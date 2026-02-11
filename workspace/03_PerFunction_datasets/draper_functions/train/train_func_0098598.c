defer() const
{
    if(!impl) return 0;
    return !((ElementImpl *)impl)->getAttribute(ATTR_DEFER).isNull();
}
