ucnv_cleanup(void) {
    ucnv_flushCache();
    if (SHARED_DATA_HASHTABLE != NULL && uhash_count(SHARED_DATA_HASHTABLE) == 0) {
        uhash_close(SHARED_DATA_HASHTABLE);
        SHARED_DATA_HASHTABLE = NULL;
    }


    ucnv_flushAvailableConverterCache();

#if !U_CHARSET_IS_UTF8
    gDefaultConverterName = NULL;
    gDefaultConverterNameBuffer[0] = 0;
    gDefaultConverterContainsOption = FALSE;
    gDefaultAlgorithmicSharedData = NULL;
#endif

    return (SHARED_DATA_HASHTABLE == NULL);
}
