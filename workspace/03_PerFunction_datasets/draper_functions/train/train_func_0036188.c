setDefault( const   Locale&     newLocale,
                            UErrorCode&  status)
{
    if (U_FAILURE(status)) {
        return;
    }


    const char *localeID = newLocale.getName();
    locale_set_default_internal(localeID, status);
}
