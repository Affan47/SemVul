ajMartDsinfoDel(AjPMartdsinfo *thys)
{
    AjPMartdsinfo pthis;
    AjPStr t = NULL;

    if(!thys)
        return;

    if(!*thys)
        return;

    pthis = *thys;

    while(ajListPop(pthis->Attributes,(void **)&t))
        ajStrDel(&t);

    while(ajListPop(pthis->Filters,(void **)&t))
        ajStrDel(&t);

    ajListFree(&pthis->Attributes);
    ajListFree(&pthis->Filters);

    ajStrDel(&pthis->Name);
    ajStrDel(&pthis->Interface);

    AJFREE(pthis);
    *thys = NULL;

    return;
}
