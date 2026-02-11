preserve_icc(SPColor *color, SPColorWheelSelector *cs){
    ColorSelector* selector = (ColorSelector*)(SP_COLOR_SELECTOR(cs)->base);
    color->icc = selector->getColor().icc ? new SVGICCColor(*selector->getColor().icc) : 0;
}
