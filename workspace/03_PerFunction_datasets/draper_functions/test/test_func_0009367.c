ajTextinDelNofile(AjPTextin* pthis)
{
    AjPTextin thys;
    AjPQueryList node = NULL;

    if(!pthis)
        return;

    thys = *pthis;

    if(!thys)
        return;

    ajDebug("ajTextinDel called qry:'%S'\n", thys->Qry);

    ajStrDel(&thys->Db);
    ajStrDel(&thys->Qry);
    ajStrDel(&thys->Formatstr);
    ajStrDel(&thys->QryFields);
    ajStrDel(&thys->Filename);

    while(ajListGetLength(thys->List))
    {
	ajListPop(thys->List, (void**) &node);
	ajStrDel(&node->Qry);
	ajStrDel(&node->Formatstr);
	AJFREE(node);
    }

    ajListFree(&thys->List);

    ajQueryDel(&thys->Query);

    AJFREE(*pthis);

    return;
}
