addThreatPercent(int32 pValue)
{
    HostileReference* ref;

    ref = getFirst();
    while (ref != NULL)
    {
        ref->addThreatPercent(pValue);
        ref = ref->next();
    }
}
