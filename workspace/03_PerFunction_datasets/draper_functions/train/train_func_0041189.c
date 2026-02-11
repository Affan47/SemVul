dbxflat_ParseIguspto(EmbPBtreeEntry entry, AjPFile inf)
{
    ajlong pos  = 0L;
    ajuint seqlen = 0;
    AjPStr tmpfd  = NULL;
    AjPStr str = NULL;
    AjPStr de = NULL;
    AjBool ok = ajTrue;

    if(!dbxflat_wrdexp)
	dbxflat_wrdexp = ajRegCompC("([A-Za-z0-9.:=]+)");

    pos = ajFileResetPos(inf);

    if(!MAJSTRGETLEN(dbxflatRdline))
        ok = ajReadlineTrim(inf,&dbxflatRdline);

    if(!ok)
    {
        ajStrDel(&dbxflatRdline);
        return ajFalse;
    }


    entry->fpos = pos;

    if(!ajStrPrefixC(dbxflatRdline,";"))
        return ajFalse;

    while(ok && ajStrPrefixC(dbxflatRdline, ";"))
    {
        ajStrAssignSubS(&de, dbxflatRdline, 2, -1);

        if(desfield && ajStrGetLen(de))
        {
            while(ajRegExec(dbxflat_wrdexp,de))
            {
                ajRegSubI(dbxflat_wrdexp, 1, &tmpfd);
                str = ajStrNew();
                ajStrAssignS(&str,tmpfd);
                ajListstrPushAppend(desfield->data, str);
                ajRegPost(dbxflat_wrdexp, &de);
            }
        }

        ok = ajReadlineTrim(inf,&dbxflatRdline);
    }

    if(!ok)
        return ajFalse;

    ajStrAssignS(&entry->id, dbxflatRdline);
    ajStrRemoveWhite(&entry->id);


    ok = ajReadlineTrim(inf,&dbxflatRdline);
    while(ok && !ajStrPrefixC(dbxflatRdline, ";"))
    {
        ajStrRemoveWhite(&dbxflatRdline);
        seqlen += MAJSTRGETLEN(dbxflatRdline);
        ok = ajReadlineTrim(inf,&dbxflatRdline);
    }

    ajStrDel(&de);
    ajStrDel(&tmpfd);

    return ajTrue;
}
