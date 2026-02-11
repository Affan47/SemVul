parseZoneID(const UnicodeString& text, ParsePosition& pos, UnicodeString& tzID) const {
    UErrorCode status = U_ZERO_ERROR;
    UBool initialized;
    UMTX_CHECK(&gLock, gZoneIdTrieInitialized, initialized);
    if (!initialized) {
        umtx_lock(&gLock);
        {
            if (!gZoneIdTrieInitialized) {
                StringEnumeration *tzenum = TimeZone::createEnumeration();
                TextTrieMap* trie = new TextTrieMap(TRUE, NULL);
                if (trie) {
                    const UnicodeString *id;
                    while ((id = tzenum->snext(status))) {
                        const UChar* uid = ZoneMeta::findTimeZoneID(*id);
                        if (uid) {
                            trie->put(uid, const_cast<UChar *>(uid), status);
                        }
                    }
                    if (U_SUCCESS(status)) {
                        gZoneIdTrie = trie;
                        gZoneIdTrieInitialized = initialized = TRUE;
                        ucln_i18n_registerCleanup(UCLN_I18N_TIMEZONEFORMAT, tzfmt_cleanup);
                    } else {
                        delete trie;
                    }
                }
                delete tzenum;
            }
        }
        umtx_unlock(&gLock);
    }

    int32_t start = pos.getIndex();
    int32_t len = 0;
    tzID.setToBogus();

    if (initialized) {
        LocalPointer<ZoneIdMatchHandler> handler(new ZoneIdMatchHandler());
        gZoneIdTrie->search(text, start, handler.getAlias(), status);
        len = handler->getMatchLen();
        if (len > 0) {
            tzID.setTo(handler->getID(), -1);
        }
    }

    if (len > 0) {
        pos.setIndex(start + len);
    } else {
        pos.setErrorIndex(start);
    }

    return tzID;
}
