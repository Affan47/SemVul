IncrementTime(UErrorCode &status) {
    fTickCounter = TIMER_INITIAL_VALUE;
    fTime++;
    if (fCallbackFn != NULL) {
        if ((*fCallbackFn)(fCallbackContext, fTime) == FALSE) {
            status = U_REGEX_STOPPED_BY_CALLER;
            return;
        }
    }
    if (fTimeLimit > 0 && fTime >= fTimeLimit) {
        status = U_REGEX_TIME_OUT;
    }
}
