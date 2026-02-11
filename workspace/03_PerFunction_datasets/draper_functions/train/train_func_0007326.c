ensQcdatabaseNewCpy(const EnsPQcdatabase qcdb)
{
    EnsPQcdatabase pthis = NULL;

    if (!qcdb)
        return NULL;

    AJNEW0(pthis);

    pthis->Use        = 1U;
    pthis->Identifier = qcdb->Identifier;
    pthis->Adaptor    = qcdb->Adaptor;

    if (qcdb->Analysis)
        pthis->Analysis = ensAnalysisNewRef(qcdb->Analysis);

    if (qcdb->Name)
        pthis->Name = ajStrNewRef(qcdb->Name);

    if (qcdb->Release)
        pthis->Release = ajStrNewRef(qcdb->Release);

    if (qcdb->Date)
        pthis->Date = ajStrNewRef(qcdb->Date);

    if (qcdb->Format)
        pthis->Format = ajStrNewRef(qcdb->Format);

    pthis->Class = qcdb->Class;
    pthis->Type  = qcdb->Type;

    if (qcdb->DatabaseadaptorSpecies)
        pthis->DatabaseadaptorSpecies = ajStrNewRef(
            qcdb->DatabaseadaptorSpecies);

    pthis->DatabaseadaptorGroup = qcdb->DatabaseadaptorGroup;

    if (qcdb->Host)
        pthis->Host = ajStrNewRef(qcdb->Host);

    if (qcdb->Directory)
        pthis->Directory = ajStrNewRef(qcdb->Directory);

    if (qcdb->File)
        pthis->File = ajStrNewRef(qcdb->File);

    if (qcdb->UrlExternal)
        pthis->UrlExternal = ajStrNewRef(qcdb->UrlExternal);

    if (qcdb->UrlInternal)
        pthis->UrlInternal = ajStrNewRef(qcdb->UrlInternal);

    return pthis;
}
