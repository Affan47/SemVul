getCEs(const CollationData &data, UErrorCode &errorCode) {
    if(U_FAILURE(errorCode)) { return; }
    int32_t i = 0;
    for(UChar c = 0;; ++i, ++c) {
        if(c == CollationFastLatin::LATIN_LIMIT) {
            c = CollationFastLatin::PUNCT_START;
        } else if(c == CollationFastLatin::PUNCT_LIMIT) {
            break;
        }
        const CollationData *d;
        uint32_t ce32 = data.getCE32(c);
        if(ce32 == Collation::FALLBACK_CE32) {
            d = data.base;
            ce32 = d->getCE32(c);
        } else {
            d = &data;
        }
        if(getCEsFromCE32(*d, c, ce32, errorCode)) {
            charCEs[i][0] = ce0;
            charCEs[i][1] = ce1;
            addUniqueCE(ce0, errorCode);
            addUniqueCE(ce1, errorCode);
        } else {

            charCEs[i][0] = ce0 = Collation::NO_CE;
            charCEs[i][1] = ce1 = 0;
        }
        if(c == 0 && !isContractionCharCE(ce0)) {


            U_ASSERT(contractionCEs.isEmpty());
            addContractionEntry(CollationFastLatin::CONTR_CHAR_MASK, ce0, ce1, errorCode);
            charCEs[0][0] = ((int64_t)Collation::NO_CE_PRIMARY << 32) | CONTRACTION_FLAG;
            charCEs[0][1] = 0;
        }
    }

    contractionCEs.addElement(CollationFastLatin::CONTR_CHAR_MASK, errorCode);
}
