type() const
{
    if(!impl) return DOMString();
    return ((ElementImpl *)impl)->getAttribute(ATTR_TYPE);
}
