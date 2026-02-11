ensGvvariationNewCpy(const EnsPGvvariation gvv)
{
    AjIList iter = NULL;

    AjPStr description = NULL;

    EnsPGvallele gva = NULL;

    EnsPGvsynonym gvsynonym = NULL;

    EnsPGvvariation pthis = NULL;

    if (!gvv)
        return NULL;

    AJNEW0(pthis);

    pthis->Use        = 1U;
    pthis->Identifier = gvv->Identifier;
    pthis->Adaptor    = gvv->Adaptor;
    pthis->Class      = ensGvattributeNewRef(gvv->Class);
    pthis->Clinical   = ensGvattributeNewRef(gvv->Clinical);
    pthis->Gvsource   = ensGvsourceNewRef(gvv->Gvsource);

    if (gvv->Name)
        pthis->Name = ajStrNewRef(gvv->Name);

    if (gvv->Ancestralallele)
        pthis->Ancestralallele = ajStrNewRef(gvv->Ancestralallele);

    if (gvv->MinoralleleAllele)
        pthis->MinoralleleAllele = ajStrNewRef(gvv->MinoralleleAllele);


    if (gvv->Gvalleles)
    {
        pthis->Gvalleles = ajListNew();

        iter = ajListIterNew(gvv->Gvalleles);

        while (!ajListIterDone(iter))
        {
            gva = (EnsPGvallele) ajListIterGet(iter);

            ajListPushAppend(pthis->Gvalleles,
                             (void *) ensGvalleleNewRef(gva));
        }

        ajListIterDel(&iter);
    }


    if (gvv->Gvsynonyms)
    {
        pthis->Gvsynonyms = ajListNew();

        iter = ajListIterNew(gvv->Gvsynonyms);

        while (!ajListIterDone(iter))
        {
            gvsynonym = (EnsPGvsynonym) ajListIterGet(iter);

            ajListPushAppend(pthis->Gvsynonyms,
                             (void *) ensGvsynonymNewRef(gvsynonym));
        }

        ajListIterDel(&iter);
    }


    if (gvv->Faileddescriptions)
    {
        pthis->Faileddescriptions = ajListstrNew();

        iter = ajListIterNew(gvv->Faileddescriptions);

        while (!ajListIterDone(iter))
        {
            description = ajListstrIterGet(iter);

            if (description)
                ajListstrPushAppend(pthis->Faileddescriptions,
                                    ajStrNewS(description));
        }

        ajListIterDel(&iter);
    }

    if (gvv->Moleculetype)
        pthis->Moleculetype = ajStrNewRef(gvv->Moleculetype);

    if (gvv->FlankFive)
        pthis->FlankFive = ajStrNewRef(gvv->FlankFive);

    if (gvv->FlankThree)
        pthis->FlankThree = ajStrNewRef(gvv->FlankThree);

    pthis->FlankExists = gvv->FlankExists;
    pthis->Somatic     = gvv->Somatic;
    pthis->Flipped     = gvv->Flipped;
    pthis->Validations = gvv->Validations;

    pthis->MinoralleleCount     = gvv->MinoralleleCount;
    pthis->MinoralleleFrequency = gvv->MinoralleleFrequency;

    return pthis;
}
