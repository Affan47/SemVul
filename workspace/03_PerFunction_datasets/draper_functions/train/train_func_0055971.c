handlesKey(const ICUServiceKey& key, UErrorCode& status) const {
    const Hashtable* supported = getSupportedIDs(status);
    if (supported) {
        UnicodeString id;
        key.currentID(id);
        return supported->get(id) != NULL;
    }
    return FALSE;
}
