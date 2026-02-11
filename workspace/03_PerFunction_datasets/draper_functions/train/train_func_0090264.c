ensAnalysisadaptorFetchAllbyFeatureclass(
    EnsPAnalysisadaptor aa,
    const AjPStr class,
    AjPList analyses)
{
    register ajuint i = 0U;
    ajuint identifier = 0U;
    ajuint match      = 0U;

    AjPSqlstatement sqls = NULL;
    AjISqlrow sqli       = NULL;
    AjPSqlrow sqlr       = NULL;

    AjPStr statement = NULL;

    EnsPAnalysis analysis = NULL;

    EnsPDatabaseadaptor dba = NULL;

    if (!aa)
        return ajFalse;

    if (!(class && ajStrGetLen(class)))
        return ajFalse;

    if (!analyses)
        return ajFalse;

    for (i = 0U; analysisadaptorKFeatureClasses[i]; i += 2U)
        if (ajStrMatchC(class, analysisadaptorKFeatureClasses[i]))
            match = i + 1U;

    if (match)
    {
        dba = ensAnalysisadaptorGetDatabaseadaptor(aa);

        statement = ajFmtStr(
            "SELECT DISTINCT %s.analysis_id FROM %s",
            analysisadaptorKFeatureClasses[match],
            analysisadaptorKFeatureClasses[match]);

        sqls = ensDatabaseadaptorSqlstatementNew(dba, statement);

        sqli = ajSqlrowiterNew(sqls);

        while (!ajSqlrowiterDone(sqli))
        {
            identifier = 0;

            sqlr = ajSqlrowiterGet(sqli);

            ajSqlcolumnToUint(sqlr, &identifier);

            ensAnalysisadaptorFetchByIdentifier(aa, identifier, &analysis);

            if (analysis)
                ajListPushAppend(analyses, (void *) analysis);
            else
                ajWarn("ensAnalysisadaptorFetchAllbyFeatureclass found "
                       "Ensembl Analysis identifier %u in the '%s' table, "
                       "which is not referenced in the 'analysis' table.\n",
                       identifier,
                       analysisadaptorKFeatureClasses[match]);
        }

        ajSqlrowiterDel(&sqli);

        ensDatabaseadaptorSqlstatementDel(dba, &sqls);

        ajStrDel(&statement);
    }
    else
    {
        ajDebug("ensAnalysisadaptorFetchAllbyFeatureclass got invalid "
                "Feature class '%S'\n",
                class);

        return ajFalse;
    }

    return ajTrue;
}
