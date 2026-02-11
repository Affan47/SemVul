isNormalized(const UnicodeString &s, UErrorCode &errorCode) const {
    uprv_checkCanGetBuffer(s, errorCode);
    if(U_FAILURE(errorCode)) {
        return FALSE;
    }
    USetSpanCondition spanCondition=USET_SPAN_SIMPLE;
    for(int32_t prevSpanLimit=0; prevSpanLimit<s.length();) {
        int32_t spanLimit=set.span(s, prevSpanLimit, spanCondition);
        if(spanCondition==USET_SPAN_NOT_CONTAINED) {
            spanCondition=USET_SPAN_SIMPLE;
        } else {
            if( !norm2.isNormalized(s.tempSubStringBetween(prevSpanLimit, spanLimit), errorCode) ||
                U_FAILURE(errorCode)
            ) {
                return FALSE;
            }
            spanCondition=USET_SPAN_NOT_CONTAINED;
        }
        prevSpanLimit=spanLimit;
    }
    return TRUE;
}
