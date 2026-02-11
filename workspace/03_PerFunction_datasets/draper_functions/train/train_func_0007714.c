findOrInsertNodeForRootCE(int64_t ce, int32_t strength, UErrorCode &errorCode) {
    if(U_FAILURE(errorCode)) { return 0; }
    U_ASSERT((uint8_t)(ce >> 56) != Collation::UNASSIGNED_IMPLICIT_BYTE);


    U_ASSERT((ce & 0xc0) == 0);
    int32_t index = findOrInsertNodeForPrimary((uint32_t)(ce >> 32) , errorCode);
    if(strength >= UCOL_SECONDARY) {
        uint32_t lower32 = (uint32_t)ce;
        index = findOrInsertWeakNode(index, lower32 >> 16, UCOL_SECONDARY, errorCode);
        if(strength >= UCOL_TERTIARY) {
            index = findOrInsertWeakNode(index, lower32 & Collation::ONLY_TERTIARY_MASK,
                                         UCOL_TERTIARY, errorCode);
        }
    }
    return index;
}
