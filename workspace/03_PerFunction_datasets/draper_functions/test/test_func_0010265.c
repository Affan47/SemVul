ensGvvariationadaptorFetchAllbyGvpopulationfrequency(
    EnsPGvvariationadaptor gvva,
    const EnsPGvpopulation gvp,
    float frequency,
    AjPList gvvs)
{


    AjBool joinallele = AJTRUE;
    AjBool joinflank  = AJFALSE;
    AjBool joinsource = AJFALSE;
    AjBool result     = AJFALSE;

    AjPStr constraint = NULL;

    if (!gvva)
        return ajFalse;

    if (!gvp)
        return ajFalse;

    if (!gvvs)
        return ajFalse;


    if (frequency > 1.0F)
        frequency /= 100.0F;

    constraint = ajFmtStr(
        "allele.sample_id = %u "
        "AND "
        "("
        "IF("
        "allele.frequency > 0.5, "
        "1 - allele.frequency, "
        "allele.frequency"
        ") > %f"
        ")",
        ensGvpopulationGetIdentifier(gvp),
        frequency);

    result = gvvariationadaptorFetchAllbyConstraint(gvva,
                                                    constraint,
                                                    joinallele,
                                                    joinflank,
                                                    joinsource,
                                                    gvvs);

    ajStrDel(&constraint);

    return result;
}
