GetNextRawFeature()
{
    if (nNextInSeq < nOffset ||
        nNextInSeq - nOffset >= (int)aosRows.size())
        return NULL;

    OGRFeature* poFeature = BuildFeatureFromSQL(aosRows[nNextInSeq - nOffset]);

    nNextInSeq ++;

    return poFeature;
}
