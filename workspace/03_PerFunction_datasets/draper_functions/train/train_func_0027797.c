localeDisplayName(const char* localeId,
                                          UnicodeString& result) const {
    return localeDisplayName(Locale(localeId), result);
}
