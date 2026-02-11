ensGvvariationfeatureadaptorFetchAllbyFrequency(
    EnsPGvvariationfeatureadaptor gvvfa,
    const EnsPGvpopulation gvp,
    float frequency,
    EnsPSlice slice,
    AjPList gvvfs)
{
    const char *const *txtcolumns = NULL;

    register ajuint i = 0U;

    AjBool result = AJFALSE;

    AjPStr columns       = NULL;
    AjPStr fvsconstraint = NULL;
    AjPStr statement     = NULL;

    EnsPBaseadaptor ba = NULL;

    if (!gvvfa)
        return ajFalse;

    if (!gvp)
        return ajFalse;

    if (!slice)
        return ajFalse;

    if (!gvvfs)
        return ajFalse;


    if (frequency > 1.0F)
        frequency /= 100.0F;


    ba = ensGvvariationfeatureadaptorGetBaseadaptor(gvvfa);

    txtcolumns = ensBaseadaptorGetColumnnames(ba);

    columns = ajStrNew();

    for (i = 0U; txtcolumns[i]; i++)
        ajFmtPrintAppS(&columns, "%s, ", txtcolumns[i]);


    ajStrCutEnd(&columns, 2);


    ensGvdatabaseadaptorFailedvariationsconstraint(
        ensGvvariationfeatureadaptorGetGvdatabaseadaptor(gvvfa),
        (const AjPStr) NULL,
        &fvsconstraint);

    statement = ajFmtStr(
        "SELECT "
        "%S "
        "FROM "
        "("
        "variation_feature vf, "
        "source, "
        "allele a"
        ") "
        "LEFT JOIN "
        "failed_variation "
        "ON "
        "(variation_feature.variation_id = failed_variation.variation_id) "
        "WHERE "
        "variation_feature.source_id = source.source_id "
        "AND "
        "variation_feature.variation_id = allele.variation_id "
        "AND "
        "allele.sample_id = %u "
        "AND "
        "("
        "IF(allele.frequency > 0.5, 1 - allele.frequency, allele.frequency) > "
        "%f"
        ") "
        "AND "
        "variation_feature.seq_region_id = %u "
        "AND "
        "variation_feature.seq_region_end > %d "
        "AND "
        "variation_feature.seq_region_start < %d "
        "AND "
        "%S "
        "GROUP BY "
        "allele.variation_id",
        columns,
        ensGvpopulationGetIdentifier(gvp),
        frequency,
        ensSliceGetSeqregionIdentifier(slice),
        ensSliceGetStart(slice),
        ensSliceGetEnd(slice),
        fvsconstraint);

    ajStrDel(&fvsconstraint);

    result = gvvariationfeatureadaptorFetchAllbyStatement(
        ba,
        statement,
        (EnsPAssemblymapper) NULL,
        (EnsPSlice) NULL,
        gvvfs);

    ajStrDel(&columns);
    ajStrDel(&statement);

    return result;
}
