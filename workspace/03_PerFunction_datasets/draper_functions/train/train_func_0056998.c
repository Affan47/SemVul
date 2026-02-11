unregister(URegistryKey rkey, UErrorCode& status)
{
    ICUServiceFactory *factory = (ICUServiceFactory*)rkey;
    UBool result = FALSE;
    if (factory != NULL && factories != NULL) {
        Mutex mutex(&lock);

        if (factories->removeElement(factory)) {
            clearCaches();
            result = TRUE;
        } else {
            status = U_ILLEGAL_ARGUMENT_ERROR;
            delete factory;
        }
    }
    if (result) {
        notifyChanged();
    }
    return result;
}
