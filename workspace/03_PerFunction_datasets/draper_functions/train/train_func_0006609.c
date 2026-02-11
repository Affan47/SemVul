ensGvpopulationadaptorFetchAllbyGvpopulationSub(
    EnsPGvpopulationadaptor gvpa,
    const EnsPGvpopulation gvp,
    AjPList gvps)
{
    AjBool result = AJFALSE;

    AjPStr statement = NULL;

    if (!gvpa)
        return ajFalse;

    if (!gvp)
        return ajFalse;

    if (!gvps)
        return ajFalse;

    if (!gvp->Identifier)
    {
        ajDebug("ensGvpopulationadaptorFetchAllbyGvpopulationSub "
                "cannot fetch Population for sub Population "
                "without identifier.\n");

        return ajFalse;
    }


    statement = ajFmtStr(
        "SELECT "
        "sample.sample_id, "
        "sample.name, "
        "sample.size, "
        "sample.description, "
        "sample.display "
        "FROM "
        "sample, "
        "population, "
        "population_structure "
        "WHERE "
        "sample.sample_id = population.sample_id "
        "AND "
        "population.sample_id = "
        "population_structure.super_population_sample_id "
        "AND "
        "population_structure.sub_population_sample_id = %u",
        gvp->Identifier);

    result = gvpopulationadaptorFetchAllbyStatement(
        gvpa,
        statement,
        (EnsPAssemblymapper) NULL,
        (EnsPSlice) NULL,
        gvps);

    ajStrDel(&statement);

    return result;
}
