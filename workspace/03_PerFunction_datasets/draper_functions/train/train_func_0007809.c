ensGvpopulationadaptorFetchAllTagged(
    EnsPGvpopulationadaptor gvpa,
    const EnsPGvvariationfeature gvvf,
    AjPList gvps)
{
    AjBool result = AJFALSE;

    AjPStr statement = NULL;

    if (!gvpa)
        return ajFalse;

    if (!gvvf)
        return ajFalse;

    if (!gvps)
        return ajFalse;

    if (!ensGvvariationfeatureGetIdentifier(gvvf))
    {
        ajDebug("ensGvpopulationadaptorFetchTagged cannot fetch a tagged "
                "Ensembl Genetic Variation Population for an "
                "Ensembl Genetic Variation Variation Feature with out an "
                "identifier.\n");

        return ajFalse;
    }

    statement = ajFmtStr(
        "SELECT "
        "sample.sample_id, "
        "sample.name, "
        "sample.size, "
        "sample.description "
        "FROM "
        "sample, "
        "population, "
        "tagged_variation_feature "
        "WHERE "
        "sample.sample_id = population.sample_id "
        "AND "
        "population.sample_id = tagged_variation_feature.sample_id "
        "AND "
        "tagged_variation_feature.tagged_variation_feature_id = %u",
        ensGvvariationfeatureGetIdentifier(gvvf));

    result = gvpopulationadaptorFetchAllbyStatement(
        gvpa,
        statement,
        (EnsPAssemblymapper) NULL,
        (EnsPSlice) NULL,
        gvps);

    ajStrDel(&statement);

    return result;
}
