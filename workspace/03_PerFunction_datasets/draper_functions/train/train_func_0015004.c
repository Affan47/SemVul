createCurrencyFormat(const Locale& locale,
                                                   UErrorCode& ec) {
    CurrencyFormat* fmt = NULL;
    if (U_SUCCESS(ec)) {
        fmt = new CurrencyFormat(locale, ec);
        if (U_FAILURE(ec)) {
            delete fmt;
            fmt = NULL;
        }
    }
    return fmt;
}
