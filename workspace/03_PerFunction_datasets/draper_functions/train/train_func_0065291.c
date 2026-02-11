ensQcdasfeatureadaptorFetchAllbyRegion(
    EnsPQcdasfeatureadaptor qcdasfa,
    const EnsPAnalysis analysis,
    const EnsPQcsequence segment,
    ajuint start,
    ajuint end,
    AjPList qcdasfs)
{
    AjBool result = AJFALSE;

    AjPStr constraint = NULL;

    if (!qcdasfa)
        return ajFalse;

    if (!analysis)
        return ajFalse;

    if (!segment)
        return ajFalse;

    if (!qcdasfs)
        return ajFalse;

    constraint = ajFmtStr(
        "das.analysis_id = %u "
        "AND "
        "das.segment_id = %u "
        "AND "
        "("
        "(das.segment_start >= %u AND das.segment_start <= %u) "
        "OR "
        "(das.segment_end >= %u AND das.segment_end <= %u) "
        "OR "
        "(das.segment_start <= %u AND das.segment_end >= %u)"
        ")",
        ensAnalysisGetIdentifier(analysis),
        ensQcsequenceGetIdentifier(segment),
        start,
        end,
        start,
        end,
        start,
        end);

    result = ensBaseadaptorFetchAllbyConstraint(
        ensQcdasfeatureadaptorGetBaseadaptor(qcdasfa),
        constraint,
        (EnsPAssemblymapper) NULL,
        (EnsPSlice) NULL,
        qcdasfs);

    ajStrDel(&constraint);

    return result;
}
