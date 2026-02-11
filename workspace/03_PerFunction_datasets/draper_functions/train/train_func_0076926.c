textEmbossQryOpen(AjPQuery qry)
{
    TextPEmbossQry qryd;
    ajint i;
    AjPStr name     = NULL;
    AjIList iter = NULL;
    AjPQueryField field = NULL;
    AjPBtcache cache = NULL;
    AjPStr qrystr = NULL;

    qry->QryData = AJNEW0(qryd);
    qryd = qry->QryData;
    qryd->div = -1;
    qryd->nentries = -1;

    qryd->Caches = ajListNew();

    if(!ajStrGetLen(qry->IndexDir))
    {
	ajDebug("no indexdir defined for database '%S'\n", qry->DbName);
	ajErr("no indexdir defined for database '%S'", qry->DbName);
	return ajFalse;
    }

    if(!textEmbossOpenCache(qry,"id",&qryd->idcache))
        return ajFalse;

    iter = ajListIterNewread(qry->QueryFields);
    while(!ajListIterDone(iter))
    {
        field = ajListIterGet(iter);
        ajStrFmtLower(&field->Wildquery);
        if(!textEmbossOpenCache(qry, MAJSTRGETPTR(field->Field), &cache))
            return ajFalse;
        ajListPushAppend(qryd->Caches, cache);
        cache = NULL;
    }
    ajListIterDel(&iter);


    ajQueryGetQuery(qry, &qrystr);

    ajDebug("directory '%S' query: '%S'\n",
	    qry->IndexDir, qrystr);

    ajStrDel(&qrystr);


    if(ajStrGetLen(qry->Exclude) && qryd->nentries >= 0)
    {
	AJCNEW0(qryd->Skip,qryd->nentries);
	name     = ajStrNew();

	for(i=0; i < qryd->nentries; ++i)
	{
	    ajStrAssignS(&name,qryd->files[i]);

	    if(!ajFilenameTestInclude(name, qry->Exclude, qry->Filename))
		qryd->Skip[i] = ajTrue;
	}

	ajStrDel(&name);
    }

    return ajTrue;
}
