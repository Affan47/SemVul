parseMappedAttribute(MappedAttribute* attr)
{
    if (attr->name() == SVGNames::typeAttr)
        setType(attr->value());
    else {
        if (SVGURIReference::parseMappedAttribute(attr))
            return;
        if (SVGExternalResourcesRequired::parseMappedAttribute(attr))
            return;

        SVGElement::parseMappedAttribute(attr);
    }
}
