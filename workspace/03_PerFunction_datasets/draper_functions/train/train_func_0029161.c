ensFeatureNewIniN(EnsPAnalysis analysis,
                              AjPStr seqname,
                              ajint start,
                              ajint end,
                              ajint strand)
{
    EnsPFeature feature = NULL;

    if (!seqname)
    {
        ajDebug("ensFeatureNewIniN requires a sequence name.\n");

        return NULL;
    }

    if (start && end && (start > (end + 1)))
    {
        ajDebug("ensFeatureNewIniN start (%d) must be less than or equal to "
                "end (%d) + 1.\n", start, end);

        return NULL;
    }

    if ((strand < -1) || (strand > 1))
    {
        ajDebug("ensFeatureNewIniN strand (%d) must be +1, 0 or -1.\n",
                strand);

        return NULL;
    }

    AJNEW0(feature);

    feature->Analysis = ensAnalysisNewRef(analysis);

    feature->Slice = NULL;

    if (seqname)
        feature->Sequencename = ajStrNewRef(seqname);

    feature->Start  = start;
    feature->End    = end;
    feature->Strand = strand;
    feature->Use    = 1U;

    return feature;
}
