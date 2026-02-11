namSvrCacheRead(const AjPStr server, const AjPStr cachename)
{
    AjPFile cachefile;
    AjPTable dbtable;
    AjPTable alitable;
    NamPEntry fnew = NULL;

    cachefile = namSvrCacheOpen(cachename);
    if(!cachefile)
        return ajFalse;

    dbtable = ajTablecharNewCase(30);
    alitable = ajTablecharNewCase(30);

    namSvrCacheParse(cachefile, dbtable, alitable);
    ajFileClose(&cachefile);

    AJNEW0(fnew);
    fnew->name = ajStrNewS(server);
    fnew->value = ajStrNewS(cachename);
    fnew->data = dbtable;
    ajTablePut(namSvrDatabaseTable, ajCharNewS(server), fnew);
    fnew = NULL;

    AJNEW0(fnew);
    fnew->name = ajStrNewS(server);
    fnew->value = ajStrNewS(cachename);
    fnew->data = alitable;
    ajTablePut(namSvrAliasTable, ajCharNewS(server), fnew);
    fnew = NULL;


    return ajTrue;
}
