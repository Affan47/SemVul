ajMartGetDatasets(AjPSeqin seqin, const AjPStr mart)
{
    AjPTable marttab = NULL;

    AjPStr spmart = NULL;
    const AjPStr host   = NULL;
    const AjPStr path   = NULL;
    const AjPStr port   = NULL;

    ajuint iport    = 0;

    AjPStr get       = NULL;

    AjPMartquery mq = NULL;
    AjPQuery qry = NULL;

    AjBool force_write = ajFalse;
    ajuint httpcode = 0;

    marttab = martGetMarttable(seqin, mart);

    if(!marttab)
    {
        ajWarn("martGetMarttable: No mart available called %S",mart);
        return ajFalse;
    }

    host = ajTableFetchC(marttab, "host");
    path = ajTableFetchC(marttab, "path");
    port = ajTableFetchC(marttab, "port");

    if(!host || !path || !port)
    {
        ajWarn("Invalid Mart location Host=%S Path=%S Port=%S",
               host,path,port);

        return ajFalse;
    }

    if(!ajStrToUint(port, &iport))
    {
        ajWarn("Invalid Port (%S)",port);

        return ajFalse;
    }


    qry = seqin->Input->Query;
    mq  = ajMartGetMartqueryPtr(seqin);

    ajStrAssignS(&mq->Marthost, host);
    ajStrAssignS(&mq->Martpath, path);
    mq->Martport = iport;


    ajStrAssignS(&mq->Mart, mart);


    if(ajStrGetLen(mq->Cachedir) && (mq->Cacheflag & MART_CACHE_RD))
    {

        if(!martReadCacheEntry(mq, &seqin->Input->Filebuff, MART_DSENTRY))
        {
            if(mq->Cacheflag & MART_CACHE_WTIFEMPTY)
                force_write = ajTrue;
            else
                force_write = ajFalse;
        }
        else
            return ajTrue;
    }


    get       = ajStrNew();
    spmart    = ajStrNew();


    ajStrAssignS(&spmart,mart);
    martSpacesToHex(&spmart);

    ajFmtPrintS(&get, "%S?type=datasets&mart=%S", path, spmart);

    ajFilebuffDel(&seqin->Input->Filebuff);

    seqin->Input->Filebuff = ajHttpRead(qry->DbHttpVer, qry->DbName,
                                        qry->DbProxy,
                                        host, iport, get);

    if(!seqin->Input->Filebuff)
	return ajFalse;

    httpcode = ajFilebuffHtmlNoheader(seqin->Input->Filebuff);
    if(httpcode)
    {
        ajWarn("ajMartGetdatasets: HTTP code %u from '%S'",
               httpcode, get);
        return ajFalse;
    }

    if((ajStrGetLen(mq->Cachedir) && (mq->Cacheflag & MART_CACHE_WT)) ||
       force_write)
    {

        martWriteCacheEntry(mq, seqin->Input->Filebuff, MART_DSENTRY);
    }

    ajStrDel(&get);
    ajStrDel(&spmart);

    return ajTrue;
}
