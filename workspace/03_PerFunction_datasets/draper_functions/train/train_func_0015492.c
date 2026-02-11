ensSeqregionadaptorFetchByName(EnsPSeqregionadaptor sra,
                                      const EnsPCoordsystem cs,
                                      const AjPStr name,
                                      EnsPSeqregion *Psr)
{
    char *txtname = NULL;

    AjBool result = AJFALSE;

    AjPList srs = NULL;

    AjPStr key       = NULL;
    AjPStr statement = NULL;

    EnsPDatabaseadaptor dba = NULL;

    EnsPSeqregion sr = NULL;

    if (ajDebugTest("ensSeqregionadaptorFetchByName"))
        ajDebug("ensSeqregionadaptorFetchByName\n"
                "  sra %p\n"
                "  cs %p\n"
                "  name '%S'\n"
                "  Psr %p",
                sra,
                cs,
                name,
                Psr);

    if (!sra)
        return ajFalse;

    if (!(name && ajStrGetLen(name)))
        return ajFalse;

    if (!Psr)
        return ajFalse;


    key = ajFmtStr("%u:%S", ensCoordsystemGetIdentifier(cs), name);

    *Psr = (EnsPSeqregion) ajTableFetchmodS(sra->CacheByName, key);

    ajStrDel(&key);

    if (*Psr)
    {
        ensSeqregionNewRef(*Psr);

        return ajTrue;
    }

    dba = ensSeqregionadaptorGetDatabaseadaptor(sra);

    ensDatabaseadaptorEscapeC(dba, &txtname, name);


    if ((!cs) || ensCoordsystemGetToplevel(cs))
        statement = ajFmtStr(
            "SELECT "
            "seq_region.seq_region_id, "
            "seq_region.name, "
            "seq_region.coord_system_id, "
            "seq_region.length "
            "FROM "
            "coord_system, "
            "seq_region "
            "WHERE "
            "coord_system.species_id = %u "
            "AND "
            "coord_system.coord_system_id = seq_region.coord_system_id "
            "AND "
            "seq_region.name = '%s' "
            "ORDER BY "
            "coord_system.rank "
            "ASC",
            ensDatabaseadaptorGetIdentifier(dba),
            txtname);
    else
        statement = ajFmtStr(
            "SELECT "
            "seq_region.seq_region_id, "
            "seq_region.name, "
            "seq_region.coord_system_id, "
            "seq_region.length "
            "FROM "
            "seq_region "
            "WHERE "
            "seq_region.coord_system_id = %u "
            "AND "
            "seq_region.name = '%s'",
            ensCoordsystemGetIdentifier(cs),
            txtname);

    ajCharDel(&txtname);

    srs = ajListNew();

    result = seqregionadaptorFetchAllbyStatement(sra, statement, srs);

    ajStrDel(&statement);


    if (ajListGetLength(srs) > 1)
        ajDebug("ensSeqregionadaptorFetchByName got more than one "
                "Ensembl Sequence Region for name '%S' and "
                "selected the one with the lowest rank.\n", name);


    ajListPop(srs, (void **) Psr);

    ensSeqregionadaptorCacheInsert(sra, Psr);

    while (ajListPop(srs, (void **) &sr))
    {
        ensSeqregionadaptorCacheInsert(sra, &sr);

        ensSeqregionDel(&sr);
    }

    ajListFree(&srs);

    return result;
}
