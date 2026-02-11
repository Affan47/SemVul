initializePattern(UStringSearch *strsrch, UErrorCode *status)
{
    if (U_FAILURE(*status)) { return 0; }
          UPattern   *pattern     = &(strsrch->pattern);
    const UChar      *patterntext = pattern->text;
          int32_t     length      = pattern->textLength;
          int32_t index       = 0;


    if (strsrch->strength == UCOL_PRIMARY) {
        pattern->hasPrefixAccents = 0;
        pattern->hasSuffixAccents = 0;
    } else {
        pattern->hasPrefixAccents = getFCD(patterntext, &index, length) >>
                                                         SECOND_LAST_BYTE_SHIFT_;
        index = length;
        U16_BACK_1(patterntext, 0, index);
        pattern->hasSuffixAccents = getFCD(patterntext, &index, length) &
                                                                 LAST_BYTE_MASK_;
    }


    if (strsrch->pattern.PCE != NULL) {
        if (strsrch->pattern.PCE != strsrch->pattern.PCEBuffer) {
            uprv_free(strsrch->pattern.PCE);
        }

        strsrch->pattern.PCE = NULL;
    }


    return initializePatternCETable(strsrch, status);
}
