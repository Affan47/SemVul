getOverflowComparisonString(const UnicodeString &lowerLimit, UErrorCode &) {
    for (int32_t i=0; i<firstScriptCharacters_->size(); i++) {
        const UnicodeString *s =
                static_cast<const UnicodeString *>(firstScriptCharacters_->elementAt(i));
        if (collator_->compare(*s, lowerLimit) > 0) {
            return *s;
        }
    }
    return *EMPTY_STRING;
}
