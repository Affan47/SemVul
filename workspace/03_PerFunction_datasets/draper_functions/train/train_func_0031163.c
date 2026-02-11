ensCoordsystemNewCpy(const EnsPCoordsystem cs)
{
    EnsPCoordsystem pthis = NULL;

    if (!cs)
        return NULL;

    AJNEW0(pthis);

    pthis->Use = 1U;

    pthis->Identifier = cs->Identifier;

    pthis->Adaptor = cs->Adaptor;

    if (cs->Name)
        pthis->Name = ajStrNewRef(cs->Name);


    if (cs->Version)
        pthis->Version = ajStrNewRef(cs->Version);
    else
        pthis->Version = ajStrNew();

    pthis->Default = cs->Default;

    pthis->SequenceLevel = cs->SequenceLevel;

    pthis->Toplevel = cs->Toplevel;

    pthis->Rank = cs->Rank;

    return pthis;
}
