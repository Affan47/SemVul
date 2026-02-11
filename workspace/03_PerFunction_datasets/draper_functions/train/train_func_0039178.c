ensGvalleleNewCpy(const EnsPGvallele gva)
{
    AjIList iter = NULL;

    AjPStr description = NULL;

    EnsPGvallele pthis = NULL;

    if (!gva)
        return NULL;

    AJNEW0(pthis);

    pthis->Use = 1U;

    pthis->Identifier = gva->Identifier;

    pthis->Adaptor = gva->Adaptor;

    pthis->Gvpopulation = ensGvpopulationNewRef(gva->Gvpopulation);

    if (gva->Allele)
        pthis->Allele = ajStrNewRef(gva->Allele);

    if (gva->Subhandle)
        pthis->Subhandle = ajStrNewRef(gva->Subhandle);


    if (gva->Faileddescriptions)
    {
        pthis->Faileddescriptions = ajListstrNew();

        iter = ajListIterNew(gva->Faileddescriptions);

        while (!ajListIterDone(iter))
        {
            description = ajListstrIterGet(iter);

            if (description)
                ajListstrPushAppend(pthis->Faileddescriptions,
                                    ajStrNewS(description));
        }

        ajListIterDel(&iter);
    }

    pthis->Counter = gva->Counter;

    pthis->Gvvariationidentifier = gva->Gvvariationidentifier;

    pthis->Subidentifier = gva->Subidentifier;

    pthis->Frequency = gva->Frequency;

    return pthis;
}
