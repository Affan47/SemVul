addChineseIndexCharacters(UErrorCode &errorCode) {
    UnicodeSet contractions;
    collatorPrimaryOnly_->internalAddContractions(BASE[0], contractions, errorCode);
    if (U_FAILURE(errorCode) || contractions.isEmpty()) { return FALSE; }
    initialLabels_->addAll(contractions);
    UnicodeSetIterator iter(contractions);
    while (iter.next()) {
        const UnicodeString &s = iter.getString();
        U_ASSERT (s.startsWith(BASE, BASE_LENGTH));
        UChar c = s.charAt(s.length() - 1);
        if (0x41 <= c && c <= 0x5A) {

            initialLabels_->add(0x41, 0x5A);
            break;
        }
    }
    return TRUE;
}
