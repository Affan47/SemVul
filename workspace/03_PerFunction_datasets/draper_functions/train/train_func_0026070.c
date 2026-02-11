ensGvindividualadaptorFetchAllbySynonym(
    EnsPGvindividualadaptor gvia,
    const AjPStr synonym,
    const AjPStr source,
    AjPList gvis)
{
    char *txtsource  = NULL;
    char *txtsynonym = NULL;

    AjBool result = AJFALSE;

    AjPStr statement = NULL;

    EnsPBaseadaptor ba = NULL;

    if (!gvia)
        return ajFalse;

    if (!synonym)
        return ajFalse;

    if (!gvis)
        return ajFalse;


    ba = ensGvindividualadaptorGetBaseadaptor(gvia);

    ensBaseadaptorEscapeC(ba, &txtsynonym, synonym);

    if (source && ajStrGetLen(source))
    {
        ensBaseadaptorEscapeC(ba, &txtsource, source);

        statement = ajFmtStr(
            "SELECT "
            "sample.sample_id, "
            "sample.name, "
            "sample.size, "
            "sample.description, "
            "sample.display, "
            "individual.gender, "
            "individual.father_individual_sample_id, "
            "individual.mother_individual_sample_id, "
            "individual_type.name, "
            "individual_type.description "
            "FROM "
            "sample, "
            "individual, "
            "individual_type, "
            "sample_synonym, "
            "source "
            "WHERE "
            "sample.sample_id = individual.sample_id "
            "AND "
            "individual.individual_type_id = "
            "individual_type.individual_type_id "
            "AND "
            "individual.sample_id = "
            "sample_synonym.sample_id "
            "AND "
            "sample_synonym.name = '%s' "
            "AND "
            "sample_synonym.source_id = source.source_id "
            "AND "
            "source.name = '%s'",
            txtsynonym,
            txtsource);

        ajCharDel(&txtsource);
    }
    else
        statement = ajFmtStr(
            "SELECT "
            "sample.sample_id, "
            "sample.name, "
            "sample.size, "
            "sample.description, "
            "sample.display, "
            "individual.gender, "
            "individual.father_individual_sample_id, "
            "individual.mother_individual_sample_id, "
            "individual_type.name, "
            "individual_type.description "
            "FROM "
            "sample, "
            "individual, "
            "individual_type, "
            "sample_synonym "
            "WHERE "
            "sample.sample_id = individual.sample_id "
            "AND "
            "individual.individual_type_id = "
            "individual_type.individual_type_id "
            "AND "
            "individual.sample_id = "
            "sample_synonym.sample_id "
            "AND "
            "sample_synonym.name = '%s'",
            txtsynonym);

    ajCharDel(&txtsynonym);

    result = gvindividualadaptorFetchAllbyStatement(
        gvia,
        statement,
        (EnsPAssemblymapper) NULL,
        (EnsPSlice) NULL,
        gvis);

    ajStrDel(&statement);

    return result;
}
