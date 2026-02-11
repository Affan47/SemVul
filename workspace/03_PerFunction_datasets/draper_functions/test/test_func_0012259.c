ensSeqregionadaptorFetchAllbyAttributecodevalue(
    EnsPSeqregionadaptor sra,
    const AjPStr code,
    const AjPStr value,
    AjPList srs)
{
    char *txtcode = NULL;
    char *txtvalue = NULL;

    AjBool result = AJFALSE;

    AjPStr statement = NULL;

    EnsPDatabaseadaptor dba = NULL;

    if (!sra)
        return ajFalse;

    if (!(code && ajStrGetLen(code)))
        return ajFalse;

    if (!srs)
        return ajFalse;

    dba = ensSeqregionadaptorGetDatabaseadaptor(sra);

    ensDatabaseadaptorEscapeC(dba, &txtcode, code);

    statement = ajFmtStr(
        "SELECT "
        "seq_region.seq_region_id, "
        "seq_region.name, "
        "seq_region.coord_system_id, "
        "seq_region.length "
        "FROM "
        "attrib_type, "
        "seq_region_attrib, "
        "seq_region "
        "WHERE "
        "attrib_type.code = '%s' "
        "AND "
        "attrib_type.attrib_type_id = seq_region_attrib.attrib_type_id "
        "AND "
        "seq_region_attrib.seq_region_id = seq_region.seq_region_id",
        txtcode);

    ajCharDel(&txtcode);

    if (value && ajStrGetLen(value))
    {
        ensDatabaseadaptorEscapeC(dba, &txtvalue, value);

        ajFmtPrintAppS(&statement,
                       " AND "
                       "seq_region_attrib.value = '%s'",
                       txtvalue);

        ajCharDel(&txtvalue);
    }

    result = seqregionadaptorFetchAllbyStatement(sra, statement, srs);

    ajStrDel(&statement);


    ajListMap(srs, &seqregionadaptorCacheInsert, (void *) sra);

    return result;
}
