markersynonymadaptorFetchAllbyStatement(
    EnsPDatabaseadaptor dba,
    const AjPStr statement,
    AjPList mss)
{
    ajuint identifier = 0U;

    AjPSqlstatement sqls = NULL;
    AjISqlrow sqli       = NULL;
    AjPSqlrow sqlr       = NULL;

    AjPStr name   = NULL;
    AjPStr source = NULL;

    EnsPMarkersynonym ms = NULL;

    if (!dba)
        return ajFalse;

    if (!statement)
        return ajFalse;

    if (!mss)
        return ajFalse;

    sqls = ensDatabaseadaptorSqlstatementNew(dba, statement);

    sqli = ajSqlrowiterNew(sqls);

    while (!ajSqlrowiterDone(sqli))
    {
        identifier = 0;
        name = ajStrNew();
        source = ajStrNew();

        sqlr = ajSqlrowiterGet(sqli);

        ajSqlcolumnToUint(sqlr, &identifier);
        ajSqlcolumnToStr(sqlr, &name);
        ajSqlcolumnToStr(sqlr, &source);

        ms = ensMarkersynonymNewIni(identifier, source, name);

        ajListPushAppend(mss, (void *) ms);

        ajStrDel(&name);
        ajStrDel(&source);
    }

    ajSqlrowiterDel(&sqli);

    ensDatabaseadaptorSqlstatementDel(dba, &sqls);

    return ajTrue;
}
