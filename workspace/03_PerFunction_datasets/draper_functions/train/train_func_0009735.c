openWords( UErrorCode &status ) const {
    if (U_FAILURE(status)) {
        return NULL;
    }
    return new MutableTrieEnumeration(fTrie, status);
}
