coordsystemadaptorFetchAllbyStatement(
    EnsPCoordsystemadaptor csa,
    const AjPStr statement,
    AjPList css)
{
    ajuint identifier = 0U;
    ajuint rank       = 0U;

    AjBool dflt     = AJFALSE;
    AjBool seqlevel = AJFALSE;
    AjBool toplevel = AJFALSE;

    AjPSqlstatement sqls = NULL;
    AjISqlrow sqli       = NULL;
    AjPSqlrow sqlr       = NULL;

    AjPStr name      = NULL;
    AjPStr version   = NULL;
    AjPStr attribute = NULL;
    AjPStr value     = NULL;

    AjPStrTok attrtoken = NULL;

    EnsPCoordsystem cs = NULL;

    EnsPDatabaseadaptor dba = NULL;

    if (!csa)
        return ajFalse;

    if (!statement)
        return ajFalse;

    if (!css)
        return ajFalse;

    dba = ensCoordsystemadaptorGetDatabaseadaptor(csa);

    sqls = ensDatabaseadaptorSqlstatementNew(dba, statement);

    sqli = ajSqlrowiterNew(sqls);

    while (!ajSqlrowiterDone(sqli))
    {
        identifier = 0;
        name       = ajStrNew();
        version    = ajStrNew();
        rank       = 0;
        attribute  = ajStrNew();

        value = ajStrNew();

        dflt     = ajFalse;
        toplevel = ajFalse;
        seqlevel = ajFalse;

        sqlr = ajSqlrowiterGet(sqli);

        ajSqlcolumnToUint(sqlr, &identifier);
        ajSqlcolumnToStr(sqlr, &name);
        ajSqlcolumnToStr(sqlr, &version);
        ajSqlcolumnToUint(sqlr, &rank);
        ajSqlcolumnToStr(sqlr, &attribute);

        attrtoken = ajStrTokenNewC(attribute, ",");

        while (ajStrTokenNextParse(attrtoken, &value))
        {
            if (ajStrMatchCaseC(value, "default_version"))
                dflt = ajTrue;

            if (ajStrMatchCaseC(value, "sequence_level"))
                seqlevel = ajTrue;
        }

        ajStrTokenDel(&attrtoken);

        cs = ensCoordsystemNewIni(csa,
                                  identifier,
                                  name,
                                  version,
                                  rank,
                                  dflt,
                                  toplevel,
                                  seqlevel);

        ajListPushAppend(css, (void *) cs);

        ajStrDel(&name);
        ajStrDel(&version);
        ajStrDel(&attribute);
        ajStrDel(&value);
    }

    ajSqlrowiterDel(&sqli);

    ensDatabaseadaptorSqlstatementDel(dba, &sqls);

    return ajTrue;
}
