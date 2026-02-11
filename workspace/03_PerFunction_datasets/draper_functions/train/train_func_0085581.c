ajUrlinDel(AjPUrlin* pthis)
{
    AjPUrlin thys;
    AjPResquery resqry;

    if(!pthis)
        return;

    thys = *pthis;

    if(!thys)
        return;

    ajDebug("ajUrlinDel called qry:'%S'\n", thys->Input->Qry);

    ajTextinDel(&thys->Input);
    ajResourceDel(&thys->Resource);

    ajStrDel(&thys->Identifiers);
    ajStrDel(&thys->Accession);
    ajStrDel(&thys->IdTypes);

    ajListstrFree(&thys->UrlList);

    while(ajListPop(thys->QryList, (void**)&resqry))
        ajResqueryDel(&resqry);
    ajListFree(&thys->QryList);

    AJFREE(*pthis);

    return;
}
