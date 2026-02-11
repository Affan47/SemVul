initializePatternPCETable(UStringSearch *strsrch,
                                          UErrorCode    *status)
{
    UPattern *pattern            = &(strsrch->pattern);
    uint32_t  pcetablesize       = INITIAL_ARRAY_SIZE_;
    int64_t  *pcetable           = pattern->PCEBuffer;
    uint32_t  patternlength      = pattern->textLength;
    UCollationElements *coleiter = strsrch->utilIter;

    if (coleiter == NULL) {
        coleiter = ucol_openElements(strsrch->collator, pattern->text,
                                     patternlength, status);


        strsrch->utilIter = coleiter;
    } else {
        uprv_init_collIterate(strsrch->collator, pattern->text,
                              pattern->textLength,
                              &coleiter->iteratordata_,
                              status);
    }
    if(U_FAILURE(*status)) {
        return 0;
    }

    if (pattern->PCE != pcetable && pattern->PCE != NULL) {
        uprv_free(pattern->PCE);
    }

    uint16_t  offset = 0;
    uint16_t  result = 0;
    int64_t   pce;

    uprv_init_pce(coleiter);


    while ((pce = ucol_nextProcessed(coleiter, NULL, NULL, status)) != UCOL_PROCESSED_NULLORDER &&
           U_SUCCESS(*status)) {
        int64_t *temp = addTouint64_tArray(pcetable, offset, &pcetablesize,
                              pce,
                              patternlength - ucol_getOffset(coleiter) + 1,
                              status);

        if (U_FAILURE(*status)) {
            return 0;
        }

        offset += 1;

        if (pcetable != temp && pcetable != pattern->PCEBuffer) {
            uprv_free(pcetable);
        }

        pcetable = temp;

    }

    pcetable[offset]   = 0;
    pattern->PCE       = pcetable;
    pattern->PCELength = offset;

    return result;
}
