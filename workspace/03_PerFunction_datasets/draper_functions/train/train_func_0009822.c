ensFeatureOverlap(const EnsPFeature feature1,
                         const EnsPFeature feature2)
{
    AjPStr name1 = NULL;
    AjPStr name2 = NULL;

    if (!feature1)
        return ajFalse;

    if (!feature2)
        return ajFalse;

    name1 = ajStrNew();
    name2 = ajStrNew();

    ensFeatureFetchSequencename(feature1, &name1);
    ensFeatureFetchSequencename(feature2, &name2);

    if ((name1 && name2) && (!ajStrMatchCaseS(name1, name2)))
    {
        ajDebug("ensFeatureOverlap got Ensembl Feature objects on different "
                "Ensembl Sequence Region objects.\n");

        ajStrDel(&name1);
        ajStrDel(&name2);

        return ajFalse;
    }

    ajStrDel(&name1);
    ajStrDel(&name2);

    return ((ensFeatureGetSeqregionEnd(feature1) >=
             ensFeatureGetSeqregionStart(feature2))
            &&
            (ensFeatureGetSeqregionStart(feature1) <=
             ensFeatureGetSeqregionEnd(feature2)));
}
