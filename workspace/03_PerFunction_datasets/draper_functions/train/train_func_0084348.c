init() {
    fFlags            = 0;
    fCompiledPat      = 0;
    fLiteralText.remove();
    fSets             = NULL;
    fSets8            = NULL;
    fDeferredStatus   = U_ZERO_ERROR;
    fMinMatchLen      = 0;
    fFrameSize        = 0;
    fDataSize         = 0;
    fGroupMap         = NULL;
    fMaxCaptureDigits = 1;
    fStaticSets       = NULL;
    fStaticSets8      = NULL;
    fStartType        = START_NO_INFO;
    fInitialStringIdx = 0;
    fInitialStringLen = 0;
    fInitialChars     = NULL;
    fInitialChar      = 0;
    fInitialChars8    = NULL;
    fNeedsAltInput    = FALSE;

    fPattern          = NULL;
    fPatternString    = NULL;
    fCompiledPat      = new UVector64(fDeferredStatus);
    fGroupMap         = new UVector32(fDeferredStatus);
    fSets             = new UVector(fDeferredStatus);
    fInitialChars     = new UnicodeSet;
    fInitialChars8    = new Regex8BitSet;
    if (U_FAILURE(fDeferredStatus)) {
        return;
    }
    if (fCompiledPat == NULL  || fGroupMap == NULL || fSets == NULL ||
        fInitialChars == NULL || fInitialChars8 == NULL) {
        fDeferredStatus = U_MEMORY_ALLOCATION_ERROR;
        return;
    }


    fSets->addElement((int32_t)0, fDeferredStatus);
}
