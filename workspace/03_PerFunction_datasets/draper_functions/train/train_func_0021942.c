ensQcdatabaseadaptorStore(EnsPQcdatabaseadaptor qcdba,
                                 EnsPQcdatabase qcdb)
{
    char *txtname        = NULL;
    char *txtrelease     = NULL;
    char *txtdate        = NULL;
    char *txtformat      = NULL;
    char *txtspecies     = NULL;
    char *txthost        = NULL;
    char *txtdirectory   = NULL;
    char *txtfile        = NULL;
    char *txtexternalurl = NULL;

    AjBool result = AJFALSE;

    AjPSqlstatement sqls = NULL;

    AjPStr statement = NULL;

    EnsPDatabaseadaptor dba = NULL;

    if (!qcdba)
        return ajFalse;

    if (!qcdb)
        return ajFalse;

    if (ensQcdatabaseGetAdaptor(qcdb) &&
        ensQcdatabaseGetIdentifier(qcdb))
        return ajFalse;

    dba = ensQcdatabaseadaptorGetDatabaseadaptor(qcdba);

    ensDatabaseadaptorEscapeC(dba, &txtname, qcdb->Name);
    ensDatabaseadaptorEscapeC(dba, &txtrelease, qcdb->Release);
    ensDatabaseadaptorEscapeC(dba, &txtdate, qcdb->Date);
    ensDatabaseadaptorEscapeC(dba, &txtformat, qcdb->Format);
    ensDatabaseadaptorEscapeC(dba, &txtspecies, qcdb->DatabaseadaptorSpecies);
    ensDatabaseadaptorEscapeC(dba, &txthost, qcdb->Host);
    ensDatabaseadaptorEscapeC(dba, &txtdirectory, qcdb->Directory);
    ensDatabaseadaptorEscapeC(dba, &txtfile, qcdb->File);
    ensDatabaseadaptorEscapeC(dba, &txtexternalurl, qcdb->UrlExternal);

    statement = ajFmtStr(
        "INSERT IGNORE INTO "
        "sequence_db "
        "SET "
        "sequence_db.analysis_id = %u, "
        "sequence_db.name = '%s', "
        "sequence_db.dbrelease = '%s', "
        "sequence_db.date = '%s', "
        "sequence_db.format = '%s' "
        "sequence_db.type = '%s', "
        "sequence_db.class = '%s', "
        "sequence_db.species = '%s', "
        "sequence_db.dbgroup = '%s', "
        "sequence_db.host = '%s', "
        "sequence_db.directory = '%s', "
        "sequence_db.file = '%s', "
        "sequence_db.external_url = '%s'",
        ensAnalysisGetIdentifier(qcdb->Analysis),
        txtname,
        txtrelease,
        txtdate,
        txtformat,
        ensQcdatabaseTypeToChar(qcdb->Type),
        ensQcdatabaseClassToChar(qcdb->Class),
        txtspecies,
        ensDatabaseadaptorGroupToChar(qcdb->DatabaseadaptorGroup),
        txthost,
        txtdirectory,
        txtfile,
        txtexternalurl);

    ajCharDel(&txtname);
    ajCharDel(&txtrelease);
    ajCharDel(&txtdate);
    ajCharDel(&txtformat);
    ajCharDel(&txtspecies);
    ajCharDel(&txthost);
    ajCharDel(&txtdirectory);
    ajCharDel(&txtfile);
    ajCharDel(&txtexternalurl);

    sqls = ensDatabaseadaptorSqlstatementNew(dba, statement);

    if (ajSqlstatementGetAffectedrows(sqls))
    {
        ensQcdatabaseSetIdentifier(qcdb, ajSqlstatementGetIdentifier(sqls));

        ensQcdatabaseSetAdaptor(qcdb, qcdba);


        qcdatabaseadaptorCacheInsert(qcdba, &qcdb);

        result = ajTrue;
    }

    ensDatabaseadaptorSqlstatementDel(dba, &sqls);

    ajStrDel(&statement);

    return result;
}
