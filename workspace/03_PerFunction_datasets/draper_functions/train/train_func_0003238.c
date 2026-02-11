ensOntologytermadaptorFetchByAccession(
    EnsPOntologytermadaptor ota,
    const AjPStr accession,
    EnsPOntologyterm *Pot)
{
    char *txtaccession = NULL;

    AjBool result = AJFALSE;

    AjPList ots = NULL;

    AjPStr statement = NULL;

    EnsPOntologyterm ot = NULL;

    if (!ota)
        return ajFalse;

    if ((accession == NULL) || (ajStrGetLen(accession) == 0))
        return ajFalse;

    if (!Pot)
        return ajFalse;

    ensBaseadaptorEscapeC(
        ensOntologytermadaptorGetBaseadaptor(ota),
        &txtaccession,
        accession);

    statement = ajFmtStr(
        "SELECT "
        "term.term_id, "
        "term.ontology_id, "
        "term.accession, "
        "term.name, "
        "term.definition, "
        "term.subsets "
        "FROM "
        "term "
        "WHERE "
        "term.accession = '%s'",
        txtaccession);

    ajCharDel(&txtaccession);

    ots = ajListNew();

    result = ontologytermadaptorFetchAllbyStatement(
        ota,
        statement,
        (EnsPAssemblymapper) NULL,
        (EnsPSlice) NULL,
        ots);

    if (ajListGetLength(ots) > 1)
        ajDebug("ensOntologytermadaptorFetchByAccession got more than one "
                "Ensembl Ontology Term for accession '%S'.\n",
                accession);

    ajListPop(ots, (void **) Pot);

    while (ajListPop(ots, (void **) &ot))
        ensOntologytermDel(&ot);

    ajListFree(&ots);

    ajStrDel(&statement);

    return result;
}
