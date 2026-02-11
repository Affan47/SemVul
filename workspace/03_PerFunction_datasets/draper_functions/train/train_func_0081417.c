ensGvsampleadaptorFetchAllbyDisplay(
    EnsPGvsampleadaptor gvsa,
    EnsEGvsampleDisplay gvsd,
    AjPList gvss)
{
    AjBool result = AJFALSE;

    AjPStr constraint = NULL;

    if (!gvsa)
        return ajFalse;

    if (!gvss)
        return ajFalse;

    constraint = ajFmtStr(
        "sample.display = '%s'",
        ensGvsampleDisplayToChar(gvsd));

    result = ensBaseadaptorFetchAllbyConstraint(
        ensGvsampleadaptorGetBaseadaptor(gvsa),
        constraint,
        (EnsPAssemblymapper) NULL,
        (EnsPSlice) NULL,
        gvss);

    ajStrDel(&constraint);

    return result;
}
