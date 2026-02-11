initIsoCodes(UErrorCode &status) {
    U_ASSERT(gIsoCodes == NULL);
    ucln_i18n_registerCleanup(UCLN_I18N_CURRENCY, currency_cleanup);

    UHashtable *isoCodes = uhash_open(uhash_hashUChars, uhash_compareUChars, NULL, &status);
    if (U_FAILURE(status)) {
        return;
    }
    uhash_setValueDeleter(isoCodes, deleteIsoCodeEntry);

    ucurr_createCurrencyList(isoCodes, &status);
    if (U_FAILURE(status)) {
        uhash_close(isoCodes);
        return;
    }
    gIsoCodes = isoCodes;

}
