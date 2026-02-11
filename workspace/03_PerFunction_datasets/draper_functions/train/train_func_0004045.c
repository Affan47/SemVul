validateChild(FWObject *o)
{
    if (FWIntervalReference::cast(o)!=NULL)  return true;
    if ( o->getId() == getAnyElementId()) return true;
    return (Interval::cast(o)!=NULL || IntervalGroup::cast(o)!=NULL);
}
