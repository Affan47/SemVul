quickCheck(const UnicodeString &s, UErrorCode &errorCode) const {
    uprv_checkCanGetBuffer(s, errorCode);
    if(U_FAILURE(errorCode)) {
        return UNORM_MAYBE;
    }
    UNormalizationCheckResult result=UNORM_YES;
    USetSpanCondition spanCondition=USET_SPAN_SIMPLE;
    for(int32_t prevSpanLimit=0; prevSpanLimit<s.length();) {
        int32_t spanLimit=set.span(s, prevSpanLimit, spanCondition);
        if(spanCondition==USET_SPAN_NOT_CONTAINED) {
            spanCondition=USET_SPAN_SIMPLE;
        } else {
            UNormalizationCheckResult qcResult=
                norm2.quickCheck(s.tempSubStringBetween(prevSpanLimit, spanLimit), errorCode);
            if(U_FAILURE(errorCode) || qcResult==UNORM_NO) {
                return qcResult;
            } else if(qcResult==UNORM_MAYBE) {
                result=qcResult;
            }
            spanCondition=USET_SPAN_NOT_CONTAINED;
        }
        prevSpanLimit=spanLimit;
    }
    return result;
}
