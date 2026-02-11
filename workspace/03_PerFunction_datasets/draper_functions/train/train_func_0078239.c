appendGroup(int32_t groupNum, UText *dest, UErrorCode &status) const {
    if (U_FAILURE(status)) {
        return 0;
    }
    if (U_FAILURE(fDeferredStatus)) {
        status = fDeferredStatus;
        return 0;
    }
    int64_t destLen = utext_nativeLength(dest);

    if (fMatch == FALSE) {
        status = U_REGEX_INVALID_STATE;
        return utext_replace(dest, destLen, destLen, NULL, 0, &status);
    }
    if (groupNum < 0 || groupNum > fPattern->fGroupMap->size()) {
        status = U_INDEX_OUTOFBOUNDS_ERROR;
        return utext_replace(dest, destLen, destLen, NULL, 0, &status);
    }

    int64_t s, e;
    if (groupNum == 0) {
        s = fMatchStart;
        e = fMatchEnd;
    } else {
        int32_t groupOffset = fPattern->fGroupMap->elementAti(groupNum-1);
        U_ASSERT(groupOffset < fPattern->fFrameSize);
        U_ASSERT(groupOffset >= 0);
        s = fFrame->fExtra[groupOffset];
        e = fFrame->fExtra[groupOffset+1];
    }

    if (s < 0) {

        return utext_replace(dest, destLen, destLen, NULL, 0, &status);
    }
    U_ASSERT(s <= e);

    int64_t deltaLen;
    if (UTEXT_FULL_TEXT_IN_CHUNK(fInputText, fInputLength)) {
        U_ASSERT(e <= fInputLength);
        deltaLen = utext_replace(dest, destLen, destLen, fInputText->chunkContents+s, (int32_t)(e-s), &status);
    } else {
        int32_t len16;
        if (UTEXT_USES_U16(fInputText)) {
            len16 = (int32_t)(e-s);
        } else {
            UErrorCode lengthStatus = U_ZERO_ERROR;
            len16 = utext_extract(fInputText, s, e, NULL, 0, &lengthStatus);
        }
        UChar *groupChars = (UChar *)uprv_malloc(sizeof(UChar)*(len16+1));
        if (groupChars == NULL) {
            status = U_MEMORY_ALLOCATION_ERROR;
            return 0;
        }
        utext_extract(fInputText, s, e, groupChars, len16+1, &status);

        deltaLen = utext_replace(dest, destLen, destLen, groupChars, len16, &status);
        uprv_free(groupChars);
    }
    return deltaLen;
}
