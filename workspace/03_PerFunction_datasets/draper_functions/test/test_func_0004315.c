openOlsonResource(const UnicodeString& id,
                                          UResourceBundle& res,
                                          UErrorCode& ec)
{
#if U_DEBUG_TZ
    char buf[128];
    id.extract(0, sizeof(buf)-1, buf, sizeof(buf), "");
#endif
    UResourceBundle *top = ures_openDirect(0, kZONEINFO, &ec);
    U_DEBUG_TZ_MSG(("pre: res sz=%d\n", ures_getSize(&res)));
     getZoneByName(top, id, &res, ec);


    U_DEBUG_TZ_MSG(("Loading zone '%s' (%s, size %d) - %s\n", buf, ures_getKey((UResourceBundle*)&res), ures_getSize(&res), u_errorName(ec)));
    if (ures_getSize(&res) <= 1 && getOlsonMeta(top)) {
        int32_t deref = ures_getInt(&res, &ec) + 0;
        U_DEBUG_TZ_MSG(("getInt: %s - type is %d\n", u_errorName(ec), ures_getType(&res)));
        UResourceBundle *ares = ures_getByKey(top, kZONES, NULL, &ec);
        ures_getByIndex(ares, deref, &res, &ec);
        ures_close(ares);
        U_DEBUG_TZ_MSG(("alias to #%d (%s) - %s\n", deref, "??", u_errorName(ec)));
    } else {
        U_DEBUG_TZ_MSG(("not an alias - size %d\n", ures_getSize(&res)));
    }
    U_DEBUG_TZ_MSG(("%s - final status is %s\n", buf, u_errorName(ec)));
    return top;
}
