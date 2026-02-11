validateChild(FWObject *o)
{
    if (FWObjectReference::cast(o)!=NULL) return true;
    if ( o->getId() == getAnyElementId()) return true;
    return ObjectGroup::validateChild(o);
}
