tryGetDecimalFallback(const UResourceBundle* numberSystemResource, const char* style, UResourceBundle** fillIn, FallbackFlags flags, UErrorCode& status) {
  UResourceBundle* first = tryGetByKeyWithFallback(numberSystemResource, style, fillIn, flags, status);
  UResourceBundle* second = tryGetByKeyWithFallback(first, gDecimalFormatTag, fillIn, flags, status);
  if (fillIn == NULL) {
    ures_close(first);
  }
  return second;
}
