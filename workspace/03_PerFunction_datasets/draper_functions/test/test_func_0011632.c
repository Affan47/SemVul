computeLevels(UBiDiLevel paragraphLevel)
{
    UErrorCode bidiStatus = U_ZERO_ERROR;

    if (fLevelRuns != NULL) {
        le_int32 ch;
        le_int32 run;

        fEmbeddingLevels = LE_NEW_ARRAY(UBiDiLevel, fCharCount);

        for (ch = 0, run = 0; run < fLevelRuns->getCount(); run += 1) {
            UBiDiLevel runLevel = (UBiDiLevel) fLevelRuns->getValue(run) | UBIDI_LEVEL_OVERRIDE;
            le_int32   runLimit = fLevelRuns->getLimit(run);

            while (ch < runLimit) {
                fEmbeddingLevels[ch++] = runLevel;
            }
        }
    }

    fParaBidi = ubidi_openSized(fCharCount, 0, &bidiStatus);
    ubidi_setPara(fParaBidi, fChars, fCharCount, paragraphLevel, fEmbeddingLevels, &bidiStatus);

    if (fLevelRuns == NULL) {
        le_int32 levelRunCount = ubidi_countRuns(fParaBidi, &bidiStatus);
        ValueRuns *levelRuns = new ValueRuns(levelRunCount);

        le_int32 logicalStart = 0;
        le_int32 run;
        le_int32 limit;
        UBiDiLevel level;

        for (run = 0; run < levelRunCount; run += 1) {
            ubidi_getLogicalRun(fParaBidi, logicalStart, &limit, &level);
            levelRuns->add(level, limit);
            logicalStart = limit;
        }

        fLevelRuns    = levelRuns;
        fClientLevels = FALSE;
    }
}
