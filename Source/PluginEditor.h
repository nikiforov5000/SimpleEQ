/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct CustomRotarySlider : juce::Slider { 
    CustomRotarySlider() : juce::Slider(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
        juce::Slider::TextEntryBoxPosition::NoTextBox) 
    
    {

    }
};

struct ResponseCurveComponent : juce::Component, juce::AudioProcessorParameter::Listener, juce::Timer {
    ResponseCurveComponent(SimpleEQAudioProcessor&);
    ~ResponseCurveComponent();
    void parameterValueChanged(int parameterIndex, float newValue) override;
    void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override { };

    void timerCallback() override;

    void paint (juce::Graphics&) override;
private:
    juce::Atomic<bool> parameterChanged{ false };
    SimpleEQAudioProcessor& audioProcessor;

    MonoChain monoChain;

};

//==============================================================================
/**
*/
class SimpleEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{

public:
    SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor&);
    ~SimpleEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleEQAudioProcessor& audioProcessor; 


    CustomRotarySlider peakFreqSlider;
    CustomRotarySlider peakGainSlider;
    CustomRotarySlider peakQualitySlider;
    CustomRotarySlider lowCutFreqSlider;
    CustomRotarySlider highCutFreqSlider;
    CustomRotarySlider lowCutSlopeSlider;
    CustomRotarySlider highCutSlopeSlider;

    ResponseCurveComponent responseCurveComponent;

    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;

    Attachment peakFreqSliderAttachment;
    Attachment peakGainSliderAttachment;
    Attachment peakQualitySliderAttachment;
    Attachment lowCutFreqSliderAttachment;
    Attachment highCutFreqSliderAttachment;
    Attachment lowCutSlopeSliderAttachment;
    Attachment highCutSlopeSliderAttachment;

    std::vector<juce::Component*> getComps();


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessorEditor)
};
