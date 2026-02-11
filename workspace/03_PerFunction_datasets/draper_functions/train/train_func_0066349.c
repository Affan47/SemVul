seqEnsemblQryFirstExon(AjPQuery qry)
{
    AjBool debug = AJFALSE;

    AjPList stableidentifiers = NULL;

    AjPStr stableidentifier = NULL;

    EnsPExonadaptor exonadaptor = NULL;

    SeqPEnsembl se = NULL;

    debug = ajDebugTest("seqEnsemblQryFirstExon");

    ajDebug("seqEnsemblQryFirstExon\n"
            "  qry %p\n",
            qry);

    if(!qry)
        return ajFalse;

    se = (SeqPEnsembl) qry->QryData;

    exonadaptor = ensRegistryGetExonadaptor(se->Databaseadaptor);

    switch(qry->QueryType)
    {
        case AJQUERY_ENTRY:

            if(debug)
                ajDebug("seqEnsemblQryFirstExon got Sequence Query type "
                        "'entry'.\n");

            ajListstrPushAppend(se->Stableidentifiers,
                                ajStrNewS(se->Wildquery));

            break;

        case AJQUERY_QUERY:

            if(debug)
                ajDebug("seqEnsemblQryFirstExon got Sequence Query type "
                        "'query'.\n");

            stableidentifiers = ajListstrNew();

            ensExonadaptorRetrieveAllStableidentifiers(exonadaptor,
                                                       stableidentifiers);

            while(ajListstrPop(stableidentifiers, &stableidentifier))
            {
                if(ajStrMatchWildS(stableidentifier, se->Wildquery))
                    ajListstrPushAppend(se->Stableidentifiers,
                                        ajStrNewS(stableidentifier));

                ajStrDel(&stableidentifier);
            }

            ajListstrFreeData(&stableidentifiers);

            break;

        case AJQUERY_ALL:

            if(debug)
                ajDebug("seqEnsemblQryFirstExon got Sequence Query type "
                        "'all'.\n");

            ensExonadaptorRetrieveAllStableidentifiers(
                exonadaptor,
                se->Stableidentifiers);

            break;

        default:

            ajDebug("seqEnsemblQryFirstExon got an unexpected "
                    "AJAX Sequence Query type %d.\n",
                    qry->QueryType);
    }

    return ajTrue;
}
