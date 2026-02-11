_cmsMallocZeroDefaultFn(cmsContext ContextID, cmsUInt32Number size)
{
    void *pt = _cmsMalloc(ContextID, size);
    if (pt == NULL) return NULL;

    memset(pt, 0, size);
    return pt;
}
