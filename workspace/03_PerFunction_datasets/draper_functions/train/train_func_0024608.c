ensDatabaseentryadaptorRetrieveAllGeneidentifiersByExternaldatabasename(
    EnsPDatabaseentryadaptor dbea,
    const AjPStr dbname,
    AjPTable identifiers)
{
    AjBool result = AJTRUE;

    AjPStr ensembltype = NULL;
    AjPStr extratype   = NULL;

    if (!dbea)
        return ajFalse;

    if (!dbname)
        return ajFalse;

    if (!identifiers)
        return ajFalse;

    ensembltype = ajStrNewC("Translation");

    extratype = ajStrNewC("gene");

    if (!databaseentryadaptorRetrieveAllIdentifiersByExternaldatabasename(
            dbea,
            dbname,
            ensembltype,
            extratype,
            identifiers))
        result = ajFalse;

    ajStrAssignC(&ensembltype, "Transcript");

    if (!databaseentryadaptorRetrieveAllIdentifiersByExternaldatabasename(
            dbea,
            dbname,
            ensembltype,
            extratype,
            identifiers))
        result = ajFalse;

    ajStrAssignC(&ensembltype, "Gene");

    if (!databaseentryadaptorRetrieveAllIdentifiersByExternaldatabasename(
            dbea,
            dbname,
            ensembltype,
            (AjPStr) NULL,
            identifiers))
        result = ajFalse;

    ajStrDel(&ensembltype);
    ajStrDel(&extratype);

    return result;
}
