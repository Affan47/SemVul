spanBackUTF8(const char *s, int32_t length, USetSpanCondition spanCondition) const {
    if(length>0 && bmpSet!=NULL) {
        const uint8_t *s0=(const uint8_t *)s;
        return bmpSet->spanBackUTF8(s0, length, spanCondition);
    }
    if(length<0) {
        length=(int32_t)uprv_strlen(s);
    }
    if(length==0) {
        return 0;
    }
    if(stringSpan!=NULL) {
        return stringSpan->spanBackUTF8((const uint8_t *)s, length, spanCondition);
    } else if(!strings->isEmpty()) {
        uint32_t which= spanCondition==USET_SPAN_NOT_CONTAINED ?
                            UnicodeSetStringSpan::BACK_UTF8_NOT_CONTAINED :
                            UnicodeSetStringSpan::BACK_UTF8_CONTAINED;
        UnicodeSetStringSpan strSpan(*this, *strings, which);
        if(strSpan.needsStringSpanUTF8()) {
            return strSpan.spanBackUTF8((const uint8_t *)s, length, spanCondition);
        }
    }

    if(spanCondition!=USET_SPAN_NOT_CONTAINED) {
        spanCondition=USET_SPAN_CONTAINED;
    }

    UChar32 c;
    int32_t prev=length;
    do {
        U8_PREV_OR_FFFD(s, 0, length, c);
        if(spanCondition!=contains(c)) {
            break;
        }
    } while((prev=length)>0);
    return prev;
}
