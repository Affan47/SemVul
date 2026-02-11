getCurrencyNameCount(const char* loc, int32_t* total_currency_name_count, int32_t* total_currency_symbol_count) {
    U_NAMESPACE_USE
    *total_currency_name_count = 0;
    *total_currency_symbol_count = 0;
    const UChar* s = NULL;
    char locale[ULOC_FULLNAME_CAPACITY];
    uprv_strcpy(locale, loc);
    const icu::Hashtable *currencySymbolsEquiv = getCurrSymbolsEquiv();
    for (;;) {
        UErrorCode ec2 = U_ZERO_ERROR;

        UResourceBundle* rb = ures_open(U_ICUDATA_CURR, locale, &ec2);
        UResourceBundle* curr = ures_getByKey(rb, CURRENCIES, NULL, &ec2);
        int32_t n = ures_getSize(curr);
        for (int32_t i=0; i<n; ++i) {
            UResourceBundle* names = ures_getByIndex(curr, i, NULL, &ec2);
            int32_t len;
            s = ures_getStringByIndex(names, UCURR_SYMBOL_NAME, &len, &ec2);
            UBool isChoice = FALSE;
            if (len > 0 && s[0] == CHOICE_FORMAT_MARK) {
                ++s;
                --len;
                if (len > 0 && s[0] != CHOICE_FORMAT_MARK) {
                    isChoice = TRUE;
                }
            }
            if (isChoice) {
                ChoiceFormat fmt(UnicodeString(TRUE, s, len), ec2);
                int32_t fmt_count;
                fmt.getFormats(fmt_count);
                *total_currency_symbol_count += fmt_count;
            } else {
                ++(*total_currency_symbol_count);
                if (currencySymbolsEquiv != NULL) {
                    *total_currency_symbol_count += countEquivalent(*currencySymbolsEquiv, UnicodeString(TRUE, s, len));
                }
            }

            ++(*total_currency_symbol_count);
            ++(*total_currency_name_count);
            ures_close(names);
        }


        UErrorCode ec3 = U_ZERO_ERROR;
        UResourceBundle* curr_p = ures_getByKey(rb, CURRENCYPLURALS, NULL, &ec3);
        n = ures_getSize(curr_p);
        for (int32_t i=0; i<n; ++i) {
            UResourceBundle* names = ures_getByIndex(curr_p, i, NULL, &ec3);
            *total_currency_name_count += ures_getSize(names);
            ures_close(names);
        }
        ures_close(curr_p);
        ures_close(curr);
        ures_close(rb);

        if (!fallback(locale)) {
            break;
        }
    }
}
