parseMappedAttribute(MappedAttribute* attr)
{
    if (attr->name() == SVGNames::x1Attr)
        setX1BaseValue(SVGLength(this, LengthModeWidth, attr->value()));
    else if (attr->name() == SVGNames::y1Attr)
        setY1BaseValue(SVGLength(this, LengthModeHeight, attr->value()));
    else if (attr->name() == SVGNames::x2Attr)
        setX2BaseValue(SVGLength(this, LengthModeWidth, attr->value()));
    else if (attr->name() == SVGNames::y2Attr)
        setY2BaseValue(SVGLength(this, LengthModeHeight, attr->value()));
    else
        SVGGradientElement::parseMappedAttribute(attr);
}
