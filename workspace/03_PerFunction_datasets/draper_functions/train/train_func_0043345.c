_appendToPat(UnicodeString& buf, const UnicodeString& s, UBool
escapeUnprintable) {
    UChar32 cp;
    for (int32_t i = 0; i < s.length(); i += U16_LENGTH(cp)) {
        _appendToPat(buf, cp = s.char32At(i), escapeUnprintable);
    }
}
