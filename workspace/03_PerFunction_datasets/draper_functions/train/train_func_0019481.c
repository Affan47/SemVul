textAccessUrl(AjPTextin textin)
{
    AjPStr host      = NULL;
    AjPStr urlget    = NULL;
    AjPStr get       = NULL;
    ajint iport;
    AjPQuery qry;

    AjIList iter = NULL;
    AjPQueryField field = NULL;

    iport = 80;
    qry = textin->Query;

    if(!ajListGetLength(qry->QueryFields))
        return ajFalse;

    if(ajStrMatchWildC(qry->DbUrl, "*%s*"))
    {
        if(ajListGetLength(qry->QueryFields))
        {
            iter = ajListIterNewread(qry->QueryFields);
            while(!ajListIterDone(iter))
            {
                field = ajListIterGet(iter);
                if(ajStrMatchC(field->Field, "id"))
                    ajStrExchangeCS(&qry->DbUrl, "%s", field->Wildquery);
                else if(qry->HasAcc && ajStrMatchC(field->Field, "acc"))
                    ajStrExchangeCS(&qry->DbUrl, "%s", field->Wildquery);
                else
                    ajStrExchangeCS(&qry->DbUrl, "%s", field->Wildquery);
            }
            ajListIterDel(&iter);
        }
    }

    if(!ajHttpQueryUrl(qry, &iport, &host, &urlget))
    {
	ajStrDel(&host);
	ajStrDel(&urlget);

	return ajFalse;
    }

    ajStrAssignS(&get, urlget);

    iter = ajListIterNewread(qry->QueryFields);
    while(!ajListIterDone(iter))
    {
        field = ajListIterGet(iter);
        if(ajStrMatchC(field->Field, "id"))
        {

            ajStrExchangeCS(&get, "%s", field->Wildquery);
        }
        else
        {
            ajDebug("Query '%S' unexpected field '%S' for URL access\n",
                  textin->Qry, field->Field);
        }
    }
    ajListIterDel(&iter);

    ajFilebuffDel(&textin->Filebuff);
    textin->Filebuff = ajHttpRead(qry->DbHttpVer, qry->DbName,
	                          qry->DbProxy, host, iport, get);

    ajStrDel(&host);
    ajStrDel(&urlget);
    ajStrDel(&get);

    if(!textin->Filebuff)
	return ajFalse;

    ajFilebuffHtmlNoheader(textin->Filebuff);

    ajFilebuffHtmlStrip(textin->Filebuff);

    ajStrAssignS(&textin->Db, qry->DbName);

    if(!qry->CaseId)
	qry->QryDone = ajTrue;

    return ajTrue;
}
