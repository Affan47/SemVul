ensQcdasfeatureNewIni(EnsPQcdasfeatureadaptor qcdasfa,
                                       ajuint identifier,
                                       EnsPQcalignment qca,
                                       EnsPAnalysis analysis,
                                       EnsPQcsequence segment,
                                       ajuint segstart,
                                       ajuint segend,
                                       ajint segstrand,
                                       EnsPQcsequence feature,
                                       ajuint fstart,
                                       ajuint fend,
                                       ajint phase,
                                       EnsEQcdasfeatureCategory category,
                                       EnsEQcdasfeatureType type)
{
    EnsPQcdasfeature qcdasf = NULL;

    if (!qca)
        return NULL;

    if (!analysis)
        return NULL;

    if (!segment)
        return NULL;

    if (!feature)
        return NULL;

    AJNEW0(qcdasf);

    qcdasf->Use             = 1U;
    qcdasf->Identifier      = identifier;
    qcdasf->Adaptor         = qcdasfa;
    qcdasf->Qcalignment     = ensQcalignmentNewRef(qca);
    qcdasf->Analysis        = ensAnalysisNewRef(analysis);
    qcdasf->SegmentSequence = ensQcsequenceNewRef(segment);
    qcdasf->SegmentStart    = segstart;
    qcdasf->SegmentEnd      = segend;
    qcdasf->SegmentStrand   = segstrand;
    qcdasf->FeatureSequence = ensQcsequenceNewRef(feature);
    qcdasf->FeatureStart    = fstart;
    qcdasf->FeatureEnd      = fend;
    qcdasf->Phase           = phase;
    qcdasf->Category        = category;
    qcdasf->Type            = type;

    return qcdasf;
}
