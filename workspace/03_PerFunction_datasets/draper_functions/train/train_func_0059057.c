nexusUnalignedDel(AjPNexusUnaligned* pthys)
{
    AjPNexusUnaligned thys;

    if (!*pthys)
        return;

    thys = *pthys;

    ajStrDel(&thys->DataType);
    ajStrDel(&thys->Symbols);
    ajStrDel(&thys->Equate);

    nexusArrayDel(&thys->Matrix);

    AJFREE(*pthys);

    return;
}
