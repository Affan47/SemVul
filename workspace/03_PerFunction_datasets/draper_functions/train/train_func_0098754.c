lookupStableName(StgPtr p)
{
    StgWord res;

    initStablePtrTable();
    ACQUIRE_LOCK(&stable_mutex);
    res = lookupStableName_(p);
    RELEASE_LOCK(&stable_mutex);
    return res;
}
