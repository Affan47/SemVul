ensGvindividualadaptorFetchAllbyParent(
    EnsPGvindividualadaptor gvia,
    const EnsPGvindividual parent,
    AjPList gvis)
{
    AjBool result = AJFALSE;

    AjPStr constraint = NULL;

    EnsPBaseadaptor ba = NULL;

    if (!gvia)
        return ajFalse;

    if (!parent)
        return ajFalse;

    if (!gvis)
        return ajFalse;

    if (!parent->Identifier)
    {
        ajDebug("ensGvindividualadaptorFetchAllbyParent cannot get Ensembl "
                "Genetic Variation Individual objects for parent Individual "
                "without identifier.\n");

        return ajFalse;
    }

    ba = ensGvindividualadaptorGetBaseadaptor(gvia);

    switch (parent->Gender)
    {
        case ensEGvindividualGenderMale:

            constraint = ajFmtStr(
                "individual.father_individual_sample_id = %u",
                parent->Identifier);

            result = ensBaseadaptorFetchAllbyConstraint(
                ba,
                constraint,
                (EnsPAssemblymapper) NULL,
                (EnsPSlice) NULL,
                gvis);

            ajStrDel(&constraint);

            return ajTrue;

            break;

        case ensEGvindividualGenderFemale:

            constraint = ajFmtStr(
                "individual.mother_individual_sample_id = %u",
                parent->Identifier);

            result = ensBaseadaptorFetchAllbyConstraint(
                ba,
                constraint,
                (EnsPAssemblymapper) NULL,
                (EnsPSlice) NULL,
                gvis);

            ajStrDel(&constraint);

            return ajTrue;

            break;

        default:


            constraint = ajFmtStr(
                "individual.father_individual_sample_id = %u",
                parent->Identifier);

            result = ensBaseadaptorFetchAllbyConstraint(
                ba,
                constraint,
                (EnsPAssemblymapper) NULL,
                (EnsPSlice) NULL,
                gvis);

            ajStrDel(&constraint);

            if (ajListGetLength(gvis))
                return ajTrue;


            constraint = ajFmtStr(
                "individual.mother_individual_sample_id = %u",
                parent->Identifier);

            result = ensBaseadaptorFetchAllbyConstraint(
                ba,
                constraint,
                (EnsPAssemblymapper) NULL,
                (EnsPSlice) NULL,
                gvis);

            ajStrDel(&constraint);

            if (ajListGetLength(gvis))
                return ajTrue;
    }


    return result;
}
