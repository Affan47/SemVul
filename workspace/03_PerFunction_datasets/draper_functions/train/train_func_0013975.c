getDisplayName(const UnicodeString& id, UnicodeString& result, const Locale& locale) const
{
    {
        ICUService* ncthis = (ICUService*)this;
        UErrorCode status = U_ZERO_ERROR;
        Mutex mutex(&ncthis->lock);
        const Hashtable* map = getVisibleIDMap(status);
        if (map != NULL) {
            ICUServiceFactory* f = (ICUServiceFactory*)map->get(id);
            if (f != NULL) {
                f->getDisplayName(id, locale, result);
                return result;
            }


            UErrorCode status = U_ZERO_ERROR;
            ICUServiceKey* fallbackKey = createKey(&id, status);
            while (fallbackKey->fallback()) {
                UnicodeString us;
                fallbackKey->currentID(us);
                f = (ICUServiceFactory*)map->get(us);
                if (f != NULL) {
                    f->getDisplayName(id, locale, result);
                    delete fallbackKey;
                    return result;
                }
            }
            delete fallbackKey;
        }
    }
    result.setToBogus();
    return result;
}
