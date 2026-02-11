isPropertyBannedFromXML(const Property* property) const
{
    if (property)
        return isPropertyBannedFromXML(property->getName());
    else
        return false;
}
