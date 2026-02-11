ensDensitytypeadaptorFetchAllbyAnalysisname(
    EnsPDensitytypeadaptor dta,
    const AjPStr name,
    AjPList dts)
{
    void **keyarray = NULL;
    void **valarray = NULL;

    register ajuint i = 0U;

    EnsPAnalysis analysis = NULL;

    if (!dta)
        return ajFalse;

    if (!name)
        return ajFalse;

    if (!dts)
        return ajFalse;

    if (!dta->CacheByIdentifier)
        densitytypeadaptorCacheInit(dta);

    ajTableToarrayKeysValues(dta->CacheByIdentifier, &keyarray, &valarray);

    for (i = 0U; keyarray[i]; i++)
    {
        analysis = ensDensitytypeGetAnalysis((EnsPDensitytype) valarray[i]);

        if (ajStrMatchS(name, ensAnalysisGetName(analysis)))
        {
            ajListPushAppend(dts, (void *)
                             ensDensitytypeNewRef((EnsPDensitytype)
                                                  valarray[i]));
        }
    }

    AJFREE(keyarray);
    AJFREE(valarray);

    return ajTrue;
}
