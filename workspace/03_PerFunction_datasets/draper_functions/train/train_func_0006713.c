ensMiscellaneoussetadaptorFetchByIdentifier(
    EnsPMiscellaneoussetadaptor msa,
    ajuint identifier,
    EnsPMiscellaneousset *Pms)
{
    AjBool result = AJFALSE;

    if (!msa)
        return ajFalse;

    if (!identifier)
        return ajFalse;

    if (!Pms)
        return ajFalse;

    *Pms = NULL;


    if (!msa->CacheByIdentifier)
        miscellaneoussetadaptorCacheInit(msa);

    *Pms = (EnsPMiscellaneousset) ajTableFetchmodV(msa->CacheByIdentifier,
                                                   (const void *) &identifier);

    if (*Pms)
    {
        ensMiscellaneoussetNewRef(*Pms);

        return ajTrue;
    }


    result = ensBaseadaptorFetchByIdentifier(
        ensMiscellaneoussetadaptorGetBaseadaptor(msa),
        identifier,
        (void **) Pms);

    miscellaneoussetadaptorCacheInsert(msa, Pms);

    return result;
}
