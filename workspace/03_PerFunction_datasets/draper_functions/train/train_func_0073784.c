optimize(const UnicodeSet &set, const char *& ,
                           UErrorCode &errorCode) {
    if(U_FAILURE(errorCode)) { return; }
    optimizeSet.addAll(set);
}
