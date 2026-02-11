ajReportDel(AjPReport* pthys)
{
    AjPReport thys;
    AjPStr str = NULL;

    thys = *pthys;

    if(!thys)
	return;

    ajStrDel(&thys->Name);
    ajStrDel(&thys->Type);
    ajStrDel(&thys->Formatstr);
    ajStrDel(&thys->Extension);

    while(ajListPop(thys->FileTypes,(void **)&str))
	ajStrDel(&str);

    ajListFree(&thys->FileTypes);

    while(ajListPop(thys->FileNames,(void **)&str))
	ajStrDel(&str);

    ajListFree(&thys->FileNames);

    while(ajListPop(thys->Tagnames,(void **)&str))
	ajStrDel(&str);

    ajListFree(&thys->Tagnames);

    while(ajListPop(thys->Tagprints,(void **)&str))
	ajStrDel(&str);

    ajListFree(&thys->Tagprints);

    while(ajListPop(thys->Tagtypes,(void **)&str))
	ajStrDel(&str);

    ajListFree(&thys->Tagtypes);

    ajStrDel(&thys->Header);
    ajStrDel(&thys->SubHeader);
    ajStrDel(&thys->Tail);
    ajStrDel(&thys->SubTail);

    ajFeattableDel(&thys->Fttable);
    ajFeattabOutDel(&thys->Ftquery);

    ajFileClose(&thys->File);

    AJFREE(*pthys);

    return;
}
