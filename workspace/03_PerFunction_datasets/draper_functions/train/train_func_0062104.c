ensFeaturepairSetTargetFeature(EnsPFeaturepair fp,
                                      EnsPFeature feature)
{
    if (ajDebugTest("ensFeaturepairSetTargetFeature"))
    {
        ajDebug("ensFeaturepairSetTargetFeature\n"
                "  fp %p\n"
                "  feature %p\n",
                fp,
                feature);

        ensFeaturepairTrace(fp, 1);

        ensFeatureTrace(feature, 1);
    }

    if (!fp)
        return ajFalse;


    ensFeatureDel(&fp->TargetFeature);

    fp->TargetFeature = ensFeatureNewRef(feature);

    return ajTrue;
}
