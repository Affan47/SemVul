ensSliceadaptorNew(
    EnsPDatabaseadaptor dba)
{
    EnsPSliceadaptor sla = NULL;

    if (!dba)
        return NULL;

    AJNEW0(sla);

    sla->Adaptor = dba;

    sla->CacheByIdentifier = ensCacheNew(
        ensECacheTypeAlphaNumeric,
        sliceadaptorKCacheMaxBytes,
        sliceadaptorKCacheMaxCount,
        sliceadaptorKCacheMaxSize,
        (void *(*)(void *)) &ensSliceNewRef,
        &sliceadaptorCacheDelete,
        (size_t (*)(const void *)) &ensSliceCalculateMemsize,
        (void *(*)(const void *key)) NULL,
        (AjBool (*)(const void *value)) NULL,
        ajFalse,
        "Slice");

    sla->CacheByName = ajTablestrNew(0U);

    ajTableSetDestroyvalue(sla->CacheByName, (void (*)(void **)) &ensSliceDel);

    return sla;
}
