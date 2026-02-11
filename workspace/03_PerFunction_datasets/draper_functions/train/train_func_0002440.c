ajMartqueryDel(AjPMartquery *thys)
{
    AjPMartquery pthis = NULL;

    if(!thys)
        return;

    if(!*thys)
        return;

    pthis = *thys;

    ajMartLocDel(&pthis->Loc);
    ajMartDatasetDel(&pthis->Dataset);
    ajMartAttributeDel(&pthis->Atts);
    ajMartFilterDel(&pthis->Filters);

    if(pthis->Config)
        ajDomDocumentDestroyNode(pthis->Config,&pthis->Config);

    ajStrDel(&pthis->Reghost);
    ajStrDel(&pthis->Regpath);
    ajStrDel(&pthis->Marthost);
    ajStrDel(&pthis->Martpath);
    ajStrDel(&pthis->Cachedir);
    ajStrDel(&pthis->Mart);
    ajStrDel(&pthis->Dsname);
    ajStrDel(&pthis->Query);

    AJFREE(pthis);

    *thys = NULL;

    return;
}
