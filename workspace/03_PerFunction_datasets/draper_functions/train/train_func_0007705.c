attributetypeadaptorCacheInsert(EnsPAttributetypeadaptor ata,
                                              EnsPAttributetype *Pat)
{
    ajuint *Pidentifier = NULL;

    EnsPAttributetype at1 = NULL;
    EnsPAttributetype at2 = NULL;

    if (!ata)
        return ajFalse;

    if (!ata->CacheByIdentifier)
        return ajFalse;

    if (!ata->CacheByCode)
        return ajFalse;

    if (!Pat)
        return ajFalse;

    if (!*Pat)
        return ajFalse;


    at1 = (EnsPAttributetype) ajTableFetchmodV(
        ata->CacheByIdentifier,
        (const void *) &((*Pat)->Identifier));


    at2 = (EnsPAttributetype) ajTableFetchmodS(
        ata->CacheByCode,
        (*Pat)->Code);

    if ((!at1) && (!at2))
    {


        AJNEW0(Pidentifier);

        *Pidentifier = (*Pat)->Identifier;

        ajTablePut(ata->CacheByIdentifier,
                   (void *) Pidentifier,
                   (void *) ensAttributetypeNewRef(*Pat));


        ajTablePut(ata->CacheByCode,
                   (void *) ajStrNewS((*Pat)->Code),
                   (void *) ensAttributetypeNewRef(*Pat));
    }

    if (at1 && at2 && (at1 == at2))
    {
        ajDebug("attributetypeadaptorCacheInsert replaced "
                "Ensembl Attribute Type %p with "
                "one already cached %p.\n",
                *Pat, at1);

        ensAttributetypeDel(Pat);

        ensAttributetypeNewRef(at1);

        Pat = &at1;
    }

    if (at1 && at2 && (at1 != at2))
        ajDebug("attributetypeadaptorCacheInsert detected "
                "Ensembl Attribute Type objects in the "
                "identifier and code cache with identical codes "
                "('%S' and '%S') but different addresses (%p and %p).\n",
                at1->Code, at2->Code, at1, at2);

    if (at1 && (!at2))
        ajDebug("attributetypeadaptorCacheInsert detected an "
                "Ensembl Attribute Type object in the identifier, "
                "but not in the code cache.\n");

    if ((!at1) && at2)
        ajDebug("attributetypeadaptorCacheInsert detected an "
                "Ensembl Attribute Type object in the code, "
                "but not in the identifier cache.\n");

    return ajTrue;
}
