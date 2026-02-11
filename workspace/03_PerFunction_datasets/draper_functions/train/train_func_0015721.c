reset(const UnicodeString &input) {
    fInputText = utext_openConstUnicodeString(fInputText, &input, &fDeferredStatus);
    if (fPattern->fNeedsAltInput) {
        fAltInputText = utext_clone(fAltInputText, fInputText, FALSE, TRUE, &fDeferredStatus);
    }
    fInputLength = utext_nativeLength(fInputText);

    reset();
    delete fInput;
    fInput = NULL;


    fInputUniStrMaybeMutable = TRUE;

    if (fWordBreakItr != NULL) {
#if UCONFIG_NO_BREAK_ITERATION==0
        UErrorCode status = U_ZERO_ERROR;
        fWordBreakItr->setText(fInputText, status);
#endif
    }
    return *this;
}
