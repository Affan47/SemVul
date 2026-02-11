ensBaseadaptorRetrieveAllStrings(
    EnsPBaseadaptor ba,
    const AjPStr tablename,
    const AjPStr columnname,
    AjPList strings)
{
    AjPSqlstatement sqls = NULL;
    AjISqlrow sqli       = NULL;
    AjPSqlrow sqlr       = NULL;

    AjPStr statement = NULL;
    AjPStr string    = NULL;

    EnsPDatabaseadaptor dba = NULL;

    if (!ba)
        return ajFalse;

    if (!tablename)
        return ajFalse;

    if (!strings)
        return ajFalse;

    statement = ajStrNew();

    baseadaptorRetrieveAllStatement(ba, tablename, columnname, &statement);

    dba = ensBaseadaptorGetDatabaseadaptor(ba);

    sqls = ensDatabaseadaptorSqlstatementNew(dba, statement);

    sqli = ajSqlrowiterNew(sqls);

    while (!ajSqlrowiterDone(sqli))
    {
        string = ajStrNew();

        sqlr = ajSqlrowiterGet(sqli);

        ajSqlcolumnToStr(sqlr, &string);

        ajListPushAppend(strings, (void *) string);
    }

    ajSqlrowiterDel(&sqli);

    ensDatabaseadaptorSqlstatementDel(dba, &sqls);

    ajStrDel(&statement);

    return ajTrue;
}
