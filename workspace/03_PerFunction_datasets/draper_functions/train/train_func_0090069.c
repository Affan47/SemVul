tryGetByKeyWithFallback(const UResourceBundle* rb, const char* path, UResourceBundle** fillIn, FallbackFlags flags, UErrorCode& status) {
  if (U_FAILURE(status)) {
    return NULL;
  }
  UBool must = (flags & MUST);
  if (rb == NULL) {
    if (must) {
      status = U_MISSING_RESOURCE_ERROR;
    }
    return NULL;
  }
  UResourceBundle* result = NULL;
  UResourceBundle* ownedByUs = NULL;
  if (fillIn == NULL) {
    ownedByUs = ures_getByKeyWithFallback(rb, path, NULL, &status);
    result = ownedByUs;
  } else {
    *fillIn = ures_getByKeyWithFallback(rb, path, *fillIn, &status);
    result = *fillIn;
  }
  if (U_FAILURE(status)) {
    ures_close(ownedByUs);
    if (status == U_MISSING_RESOURCE_ERROR && !must) {
      status = U_ZERO_ERROR;
    }
    return NULL;
  }
  flags = (FallbackFlags) (flags & ~MUST);
  switch (flags) {
    case NOT_ROOT:
      {
        UBool bRoot = isRoot(result, status);
        if (bRoot || U_FAILURE(status)) {
          ures_close(ownedByUs);
          if (must && (status == U_ZERO_ERROR)) {
            status = U_MISSING_RESOURCE_ERROR;
          }
          return NULL;
        }
        return result;
      }
    case ANY:
      return result;
    default:
      ures_close(ownedByUs);
      status = U_ILLEGAL_ARGUMENT_ERROR;
      return NULL;
  }
}
