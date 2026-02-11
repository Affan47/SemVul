handleTransliterate(Replaceable& text, UTransPosition& index,
                                               UBool ) const {


    UnicodeString empty;
    text.handleReplaceBetween(index.start, index.limit, empty);
    int32_t len = index.limit - index.start;
    index.contextLimit -= len;
    index.limit -= len;
}
