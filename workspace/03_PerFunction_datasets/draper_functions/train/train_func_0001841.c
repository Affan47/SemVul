js_GetLocalizedErrorMessage(JSContext* cx, void *userRef, const char *locale,
                            const uintN errorNumber)
{
    const JSErrorFormatString *errorString = NULL;

    if (cx->localeCallbacks && cx->localeCallbacks->localeGetErrorMessage) {
        errorString = cx->localeCallbacks
                        ->localeGetErrorMessage(userRef, locale, errorNumber);
    }
    if (!errorString)
        errorString = js_GetErrorMessage(userRef, locale, errorNumber);
    return errorString;
}
