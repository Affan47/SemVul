unregister(URegistryKey key, UErrorCode& status)
{
    if (U_FAILURE(status)) {
        return FALSE;
    }
    if (haveService()) {
        return gService->unregister(key, status);
    } else {
        status = U_ILLEGAL_ARGUMENT_ERROR;
        return FALSE;
    }
}
