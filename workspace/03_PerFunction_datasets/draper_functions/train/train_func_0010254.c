sliderMoved(Slider* slider)
    {
        if (slider->getName() == "RealSlider")
        {
            global_real = slider->getValue();
        }
        else if (slider->getName() == "ImagSlider")
        {
            global_imag = slider->getValue();
        }
        else if (slider->getName() == "ThetaSlider")
        {
            global_theta = slider->getValue();
        }
        generate();
    }
