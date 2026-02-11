isKnownAttribute(const QualifiedName& attrName)
{

    int propId = SVGStyledElement::cssPropertyIdForSVGAttributeName(attrName);
    if (propId > 0)
        return true;
    return (attrName.id() == ATTR_ID || attrName.id() == ATTR_STYLE);

}
