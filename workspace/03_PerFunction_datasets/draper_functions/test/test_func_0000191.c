computeHashCode(const uint8_t *key, int32_t  length) {
    const char *s = reinterpret_cast<const char *>(key);
    int32_t hash;
    if (s == NULL || length == 0) {
        hash = kEmptyHashCode;
    } else {
        hash = ustr_hashCharsN(s, length);
        if (hash == kInvalidHashCode || hash == kBogusHashCode) {
            hash = kEmptyHashCode;
        }
    }
    return hash;
}
