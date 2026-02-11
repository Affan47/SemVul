getEngineFor(UChar32 c, int32_t breakType) {
    UBool       needsInit;
    int32_t     i;
    const LanguageBreakEngine *lbe = NULL;
    UErrorCode  status = U_ZERO_ERROR;


    umtx_lock(NULL);
    needsInit = (UBool)(fEngines == NULL);
    if (!needsInit) {
        i = fEngines->size();
        while (--i >= 0) {
            lbe = (const LanguageBreakEngine *)(fEngines->elementAt(i));
            if (lbe != NULL && lbe->handles(c, breakType)) {
                break;
            }
            lbe = NULL;
        }
    }
    umtx_unlock(NULL);

    if (lbe != NULL) {
        return lbe;
    }

    if (needsInit) {
        UStack  *engines = new UStack(_deleteEngine, NULL, status);
        if (U_SUCCESS(status) && engines == NULL) {
            status = U_MEMORY_ALLOCATION_ERROR;
        }
        else if (U_FAILURE(status)) {
            delete engines;
            engines = NULL;
        }
        else {
            umtx_lock(NULL);
            if (fEngines == NULL) {
                fEngines = engines;
                engines = NULL;
            }
            umtx_unlock(NULL);
            delete engines;
        }
    }

    if (fEngines == NULL) {
        return NULL;
    }


    const LanguageBreakEngine *newlbe = loadEngineFor(c, breakType);


    umtx_lock(NULL);
    i = fEngines->size();
    while (--i >= 0) {
        lbe = (const LanguageBreakEngine *)(fEngines->elementAt(i));
        if (lbe != NULL && lbe->handles(c, breakType)) {
            break;
        }
        lbe = NULL;
    }
    if (lbe == NULL && newlbe != NULL) {
        fEngines->push((void *)newlbe, status);
        lbe = newlbe;
        newlbe = NULL;
    }
    umtx_unlock(NULL);

    delete newlbe;

    return lbe;
}
