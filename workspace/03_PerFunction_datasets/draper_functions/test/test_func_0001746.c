create(const ICUServiceKey& key, const ICUService* service, UErrorCode& status) const
{
    if (U_SUCCESS(status)) {
        UnicodeString temp;
        if (_id == key.currentID(temp)) {
            return service->cloneInstance(_instance);
        }
    }
    return NULL;
}
