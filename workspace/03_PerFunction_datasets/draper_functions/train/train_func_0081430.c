addIfDifferent(const UnicodeString &prefix, const UnicodeString &str,
                                 const int64_t newCEs[], int32_t newCEsLength, uint32_t ce32,
                                 UErrorCode &errorCode) {
    if(U_FAILURE(errorCode)) { return ce32; }
    int64_t oldCEs[Collation::MAX_EXPANSION_LENGTH];
    int32_t oldCEsLength = dataBuilder->getCEs(prefix, str, oldCEs, 0);
    if(!sameCEs(newCEs, newCEsLength, oldCEs, oldCEsLength)) {
        if(ce32 == Collation::UNASSIGNED_CE32) {
            ce32 = dataBuilder->encodeCEs(newCEs, newCEsLength, errorCode);
        }
        dataBuilder->addCE32(prefix, str, ce32, errorCode);
    }
    return ce32;
}
