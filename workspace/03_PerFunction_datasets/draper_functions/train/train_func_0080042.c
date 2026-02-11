locale_cleanup(void)
{
    U_NAMESPACE_USE

    if (availableLocaleList) {
        delete []availableLocaleList;
        availableLocaleList = NULL;
    }
    availableLocaleListCount = 0;

    if (gLocaleCache) {
        delete [] gLocaleCache;
        gLocaleCache = NULL;
    }

    if (gDefaultLocalesHashT) {
        uhash_close(gDefaultLocalesHashT);
        gDefaultLocalesHashT = NULL;
    }
    else if (gDefaultLocale) {

        delete gDefaultLocale;
    }
    gDefaultLocale = NULL;

    return TRUE;
}
