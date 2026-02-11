findBreaks( UText *text,
                                 int32_t startPos,
                                 int32_t endPos,
                                 UBool reverse,
                                 int32_t breakType,
                                 UStack & ) const {
    if (breakType >= 0 && breakType < (int32_t)(sizeof(fHandled)/sizeof(fHandled[0]))) {
        UChar32 c = utext_current32(text);
        if (reverse) {
            while((int32_t)utext_getNativeIndex(text) > startPos && fHandled[breakType]->contains(c)) {
                c = utext_previous32(text);
            }
        }
        else {
            while((int32_t)utext_getNativeIndex(text) < endPos && fHandled[breakType]->contains(c)) {
                utext_next32(text);
                c = utext_current32(text);
            }
        }
    }
    return 0;
}
