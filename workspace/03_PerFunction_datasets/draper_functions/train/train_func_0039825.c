ensQcdasfeatureTrace(const EnsPQcdasfeature qcdasf, ajuint level)
{
    AjPStr indent = NULL;

    if (!qcdasf)
        return ajFalse;

    indent = ajStrNew();

    ajStrAppendCountK(&indent, ' ', level * 2);

    ajDebug("%SensQcdasfeatureTrace %p\n"
            "%S  Use %u\n"
            "%S  Identifier %u\n"
            "%S  Adaptor %p\n"
            "%S  Qcalignment %p\n"
            "%S  Analysis %p\n"
            "%S  SegmentSequence %p\n"
            "%S  FeatureSequence %p\n"
            "%S  SegmentStart %u\n"
            "%S  SegmentEnd %u\n"
            "%S  SegmentStrand %d\n"
            "%S  FeatureStart %u\n"
            "%S  FeatureEnd %u\n"
            "%S  Phase %d\n"
            "%S  Category '%s'\n"
            "%S  Type '%s'\n",
            indent, qcdasf,
            indent, qcdasf->Use,
            indent, qcdasf->Identifier,
            indent, qcdasf->Adaptor,
            indent, qcdasf->Qcalignment,
            indent, qcdasf->Analysis,
            indent, qcdasf->SegmentSequence,
            indent, qcdasf->FeatureSequence,
            indent, qcdasf->SegmentStart,
            indent, qcdasf->SegmentEnd,
            indent, qcdasf->SegmentStrand,
            indent, qcdasf->FeatureStart,
            indent, qcdasf->FeatureEnd,
            indent, qcdasf->Phase,
            indent, ensQcdasfeatureCategoryToChar(qcdasf->Category),
            indent, ensQcdasfeatureTypeToChar(qcdasf->Type));

    ensAnalysisTrace(qcdasf->Analysis, 1);

    ensQcalignmentTrace(qcdasf->Qcalignment, 1);

    ensQcsequenceTrace(qcdasf->SegmentSequence, 1);
    ensQcsequenceTrace(qcdasf->FeatureSequence, 1);

    ajStrDel(&indent);

    return ajTrue;
}
