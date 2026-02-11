getPropertyPriority(const DOMString &propertyName) const
{
    int propID = propertyID(propertyName);
    if (!propID)
        return DOMString();
    return getPropertyPriority(propID) ? "important" : "";
}
