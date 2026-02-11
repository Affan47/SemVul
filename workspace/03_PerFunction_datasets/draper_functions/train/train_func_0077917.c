_sliderReleased( SPColorSlider *slider, SPColorWheelSelector *cs )
{
    (void)slider;
    ColorWheelSelector* wheelSelector = (ColorWheelSelector*)(SP_COLOR_SELECTOR(cs)->base);
    if (wheelSelector->_dragging) {
        wheelSelector->_dragging = FALSE;
        wheelSelector->_released();

        preserve_icc(&wheelSelector->_color, cs);
        wheelSelector->_updateInternals( wheelSelector->_color, ColorScales::getScaled( wheelSelector->_adj ), wheelSelector->_dragging );
    }
}
