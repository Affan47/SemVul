handleDefault(const ICUServiceKey& key, UnicodeString* , UErrorCode& status) const {
        LocaleKey& lkey = (LocaleKey&)key;


        Locale loc;
        lkey.canonicalLocale(loc);

#ifdef U_DEBUG_CALSVC
        Locale loc2;
        lkey.currentLocale(loc2);
        fprintf(stderr, "CalSvc:handleDefault for currentLoc %s, canloc %s\n", (const char*)loc.getName(),  (const char*)loc2.getName());
#endif
        Calendar *nc =  new GregorianCalendar(loc, status);

#ifdef U_DEBUG_CALSVC
        UErrorCode status2 = U_ZERO_ERROR;
        fprintf(stderr, "New default calendar has tz=%d\n", ((Calendar*)nc)->get(UCAL_ZONE_OFFSET, status2));
#endif
        return nc;
    }
