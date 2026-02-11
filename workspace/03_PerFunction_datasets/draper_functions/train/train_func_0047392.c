ensMiscellaneousfeatureadaptorFetchAllbyAttributecodevalue(
    EnsPMiscellaneousfeatureadaptor mfa,
    const AjPStr code,
    const AjPStr value,
    AjPList mfs)
{
    register ajuint i = 0U;

    ajuint mfid = 0U;

    char *txtvalue = NULL;

    const char *template = "misc_feature.misc_feature_id in (%S)";

    AjPSqlstatement sqls = NULL;
    AjISqlrow sqli       = NULL;
    AjPSqlrow sqlr       = NULL;

    AjPStr csv        = NULL;
    AjPStr constraint = NULL;
    AjPStr statement  = NULL;

    EnsPAttributetype at = NULL;

    EnsPBaseadaptor ba = NULL;

    EnsPDatabaseadaptor dba = NULL;

    if (!mfa)
        return ajFalse;

    if (!code)
        ajFatal("ensMiscellaneousfeatureadaptorFetchAllbyAttributecodevalue "
                "requires an Ensembl Attribute code.\n");

    ba  = ensMiscellaneousfeatureadaptorGetBaseadaptor(mfa);

    dba = ensBaseadaptorGetDatabaseadaptor(ba);

    ensAttributetypeadaptorFetchByCode(
        ensRegistryGetAttributetypeadaptor(dba),
        code,
        &at);

    if (!at)
        return ajTrue;


    statement = ajFmtStr(
        "SELECT DISTINCT "
        "misc_attrib.misc_feature_id "
        "FROM "
        "misc_attrib, "
        "misc_feature, "
        "seq_region, "
        "coord_system "
        "WHERE "
        "misc_attrib.attrib_type_id = %u "
        "AND "
        "misc_attrib.misc_feature_id = misc_feature.misc_feature_id "
        "AND "
        "misc_feature.seq_region_id = seq_region.seq_region_id "
        "AND "
        "seq_region.coord_system_id = coord_system.coord_system_id "
        "AND "
        "coord_system.species_id = %u",
        ensAttributetypeGetIdentifier(at),
        ensDatabaseadaptorGetIdentifier(dba));

    if (value)
    {
        ensDatabaseadaptorEscapeC(dba, &txtvalue, value);

        ajFmtPrintAppS(&statement, " AND misc_attrib.value = '%s'", txtvalue);

        ajCharDel(&txtvalue);
    }

    sqls = ensDatabaseadaptorSqlstatementNew(dba, statement);

    sqli = ajSqlrowiterNew(sqls);

    csv = ajStrNew();


    while (!ajSqlrowiterDone(sqli))
    {
        mfid = 0;

        sqlr = ajSqlrowiterGet(sqli);

        ajSqlcolumnToUint(sqlr, &mfid);

        ajFmtPrintAppS(&csv, "%u, ", mfid);


        if ((((i + 1U) % ensKBaseadaptorMaximumIdentifiers) == 0) ||
            ajSqlrowiterDone(sqli))
        {


            ajStrCutEnd(&csv, 2);

            if (ajStrGetLen(csv))
            {
                constraint = ajFmtStr(template, csv);

                ensBaseadaptorFetchAllbyConstraint(
                    ba,
                    constraint,
                    (EnsPAssemblymapper) NULL,
                    (EnsPSlice) NULL,
                    mfs);

                ajStrDel(&constraint);
            }

            ajStrSetClear(&csv);
        }

        i++;
    }

    ajSqlrowiterDel(&sqli);

    ensDatabaseadaptorSqlstatementDel(dba, &sqls);

    ajStrDel(&statement);

    ajStrDel(&csv);

    return ajTrue;
}
