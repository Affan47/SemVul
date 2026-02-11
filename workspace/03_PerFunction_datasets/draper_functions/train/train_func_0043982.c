timeZone_cleanup(void)
{
#ifdef U_USE_TIMEZONE_OBSOLETE_2_8
    delete []OLSON_IDS;
    OLSON_IDS = 0;
#endif

    delete DEFAULT_ZONE;
    DEFAULT_ZONE = NULL;

    delete _GMT;
    _GMT = NULL;

    uprv_memset(TZDATA_VERSION, 0, sizeof(TZDATA_VERSION));
    TZDataVersionInitialized = FALSE;

    if (LOCK) {
        umtx_destroy(&LOCK);
        LOCK = NULL;
    }
    if (TZSET_LOCK) {
        umtx_destroy(&TZSET_LOCK);
        TZSET_LOCK = NULL;
    }

    return TRUE;
}
