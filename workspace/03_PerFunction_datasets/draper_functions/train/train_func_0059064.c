ajDasServerDel(AjPDasServer *thys)
{
    AjPDasServer pthis = NULL;
    AjPDasSource source;
    AjPDasCoordinate coord;
    AjIList iter;
    AjIList iterc;

    if(!thys)
        return;

    if(!*thys)
        return;

    pthis = *thys;

    ajStrDel(&pthis->host);
    ajStrDel(&pthis->path);

    iter = ajListIterNew(pthis->sources);

    while(!ajListIterDone(iter))
    {
	source = ajListIterGet(iter);
        ajStrDel(&source->uri);
        ajStrDel(&source->title);
        ajStrDel(&source->description);
        ajStrDel(&source->sequence_query_uri);
        ajStrDel(&source->entry_points_uri);
        ajStrDel(&source->features_query_uri);

        iterc = ajListIterNew(source->coordinates);

        while(!ajListIterDone(iterc))
        {
            coord = ajListIterGet(iterc);
            ajStrDel(&coord->authority);
            ajStrDel(&coord->source);
            ajStrDel(&coord->taxid);
            ajStrDel(&coord->test_range);
            ajStrDel(&coord->uri);
            ajStrDel(&coord->version);
            AJFREE(coord);
        }

        ajListFree(&source->coordinates);
        AJFREE(source);
        ajListIterDel(&iterc);
    }

    ajListIterDel(&iter);
    ajListFree(&pthis->sources);

    AJFREE(pthis);

    *thys = NULL;

    return;
}
