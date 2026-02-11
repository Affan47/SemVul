getMatchCallback(URegexMatchCallback   *&callback,
                                  const void              *&context,
                                  UErrorCode              &status) {
    if (U_FAILURE(status)) {
       return;
    }
    callback = fCallbackFn;
    context  = fCallbackContext;
}
