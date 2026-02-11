isRoot(const UResourceBundle* rb, UErrorCode& status) {
  const char* actualLocale = ures_getLocaleByType(
      rb, ULOC_ACTUAL_LOCALE, &status);
  if (U_FAILURE(status)) {
    return FALSE;
  }
  return uprv_strcmp(actualLocale, gRoot) == 0;
}
