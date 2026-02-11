createAttributeMap() const
{
    namedAttrMap = new NamedAttrMapImpl(const_cast<ElementImpl*>(this));
    namedAttrMap->ref();
}
