gvattributeadaptorCacheInit(EnsPGvattributeadaptor gvaa)
{
    AjBool result = AJFALSE;

    AjPList gvas = NULL;

    EnsPGvattribute gva = NULL;

    if (ajDebugTest("gvattributeadaptorCacheInit"))
        ajDebug("gvattributeadaptorCacheInit\n"
                "  gvaa %p\n",
                gvaa);

    if (!gvaa)
        return ajFalse;

    if (gvaa->CacheByIdentifier)
        return ajFalse;
    else
    {
        gvaa->CacheByIdentifier = ajTableuintNew(0U);

        ajTableSetDestroyvalue(
            gvaa->CacheByIdentifier,
            (void (*)(void **)) &ensGvattributeDel);
    }

    gvas = ajListNew();

    result = ensBaseadaptorFetchAll(
        ensGvattributeadaptorGetBaseadaptor(gvaa),
        gvas);

    while (ajListPop(gvas, (void **) &gva))
    {
        gvattributeadaptorCacheInsert(gvaa, &gva);


        ensGvattributeDel(&gva);
    }

    ajListFree(&gvas);

    return result;
}
