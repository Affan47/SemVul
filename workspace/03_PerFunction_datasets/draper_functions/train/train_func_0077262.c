getFeatureTable(le_uint16 featureIndex, LETag *featureTag) const
{
    if (featureIndex >= SWAPW(featureCount)) {
        return 0;
    }

    Offset featureTableOffset = featureRecordArray[featureIndex].featureTableOffset;

    *featureTag = SWAPT(featureRecordArray[featureIndex].featureTag);

    return (const FeatureTable *) ((char *) this + SWAPW(featureTableOffset));
}
