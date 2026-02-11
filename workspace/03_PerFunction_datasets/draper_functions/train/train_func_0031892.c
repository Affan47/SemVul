next(void) {


    if (fCachedBreakPositions != NULL) {
        if (fPositionInCache < fNumCachedBreakPositions - 1) {
            ++fPositionInCache;
            int32_t pos = fCachedBreakPositions[fPositionInCache];
            utext_setNativeIndex(fText, pos);
            return pos;
        }
        else {
            reset();
        }
    }

    int32_t startPos = current();
    int32_t result = handleNext(fData->fForwardTable);
    if (fDictionaryCharCount > 0) {
        result = checkDictionary(startPos, result, FALSE);
    }
    return result;
}
