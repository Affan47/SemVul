ensGvpopulationgenotypeadaptorFetchAllbyGvpopulation(
    EnsPGvpopulationgenotypeadaptor gvpga,
    const EnsPGvpopulation gvp,
    AjPList gvpgs)
{
    AjBool result = AJFALSE;

    AjPStr constraint    = NULL;
    AjPStr fvsconstraint = NULL;

    if (!gvpga)
        return ajFalse;

    if (!gvp)
        return ajFalse;

    if (!gvpgs)
        return ajFalse;

    if (ensGvpopulationGetIdentifier(gvp) == 0)
    {
        ajDebug("ensGvpopulationgenotypeadaptorFetchAllbyGvpopulation "
                "got Ensembl Genetic Variation Population without "
                "identifier.n");

        return ajFalse;
    }

    ensGvdatabaseadaptorFailedvariationsconstraint(
        ensGvpopulationgenotypeadaptorGetGvdatabaseadaptor(gvpga),
        (const AjPStr) NULL,
        &fvsconstraint);

    constraint = ajFmtStr("population_genotype.sample_id = %u AND %S",
                          ensGvpopulationGetIdentifier(gvp),
                          fvsconstraint);

    result = ensBaseadaptorFetchAllbyConstraint(
        ensGvpopulationgenotypeadaptorGetBaseadaptor(gvpga),
        constraint,
        (EnsPAssemblymapper) NULL,
        (EnsPSlice) NULL,
        gvpgs);

    ajStrDel(&constraint);
    ajStrDel(&fvsconstraint);

    return result;
}
