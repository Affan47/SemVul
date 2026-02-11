isAny() const
{
    if (getChildrenCount()!=1) return(false);
    const FWObject *o = front();
    return ((FWReference::constcast(o))->getPointerIdDirect() == getAnyElementId());
}
