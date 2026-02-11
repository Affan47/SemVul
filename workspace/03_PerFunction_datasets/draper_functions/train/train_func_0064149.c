ensQcsequenceadaptorFetchAllbyQcdatabase(EnsPQcsequenceadaptor qcsa,
                                                const EnsPQcdatabase qcdb,
                                                AjPList qcss)
{
    AjBool result = AJFALSE;

    AjPStr constraint = NULL;

    if (!qcsa)
        return ajFalse;

    if (!qcdb)
        return ajFalse;

    if (!qcss)
        return ajFalse;

    constraint = ajFmtStr("sequence.sequence_db_id = %u",
                          ensQcdatabaseGetIdentifier(qcdb));

    result = ensBaseadaptorFetchAllbyConstraint(
        ensQcsequenceadaptorGetBaseadaptor(qcsa),
        constraint,
        (EnsPAssemblymapper) NULL,
        (EnsPSlice) NULL,
        qcss);

    ajStrDel(&constraint);

    return result;
}
