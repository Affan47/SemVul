ajTextinAccessFtp(AjPTextin textin)
{
    AjPQuery qry;
    AjPStr url = NULL;

    AjPStr host  = NULL;
    ajint iport;

    AjPStr urlget    = NULL;
    AjPUrlref urlref = NULL;

    iport = 21;
    qry = textin->Query;

    if(!ajStrGetLen(qry->Filename))
    {
	ajErr("FILE access: no filename");

	return ajFalse;
    }

    ajDebug("ajTextinAccessFtp %S\n", qry->Filename);


    ajStrAssignS(&url, qry->Filename);

    urlref = ajHttpUrlrefNew();
    ajHttpUrlrefParseS(&urlref, url);
    ajHttpUrlrefSplitPort(urlref);
    ajStrAssignS(&host,urlref->Host);
    if(ajStrGetLen(urlref->Port))
        ajStrToInt(urlref->Port, &iport);
    ajFmtPrintS(&urlget,"/%S",urlref->Absolute);
    ajHttpUrlrefDel(&urlref);

    ajFilebuffDel(&textin->Filebuff);
    textin->Filebuff = ajFtpRead(NULL, host, iport, textin->Fpos, urlget);

    ajStrDel(&host);
    ajStrDel(&urlget);

    if(!textin->Filebuff)
    {
	ajDebug("FTP access: unable to open file '%S'\n", qry->Filename);

	return ajFalse;
    }


    ajStrAssignS(&textin->Filename, qry->Filename);

    ajDebug("FTP access: opened file '%S'\n", qry->Filename);

    ajStrDel(&url);

    return ajTrue;
}
