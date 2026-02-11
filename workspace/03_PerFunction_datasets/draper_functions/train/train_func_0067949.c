ucurr_countCurrencyList(UEnumeration *enumerator, UErrorCode * ) {
    UCurrencyContext *myContext = (UCurrencyContext *)(enumerator->context);
    uint32_t currType = myContext->currType;
    int32_t count = 0;


    for (int32_t idx = 0; gCurrencyList[idx].currency != NULL; idx++) {
        if (UCURR_MATCHES_BITMASK(gCurrencyList[idx].currType, currType)) {
            count++;
        }
    }
    return count;
}
