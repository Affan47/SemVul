nextCE32FromContraction(const CollationData *d, uint32_t contractionCE32,
                                           const UChar *p, uint32_t ce32, UChar32 c,
                                           UErrorCode &errorCode) {


    int32_t lookAhead = 1;

    int32_t sinceMatch = 1;


    UCharsTrie suffixes(p);
    if(skipped != NULL && !skipped->isEmpty()) { skipped->saveTrieState(suffixes); }
    UStringTrieResult match = suffixes.firstForCodePoint(c);
    for(;;) {
        UChar32 nextCp;
        if(USTRINGTRIE_HAS_VALUE(match)) {
            ce32 = (uint32_t)suffixes.getValue();
            if(!USTRINGTRIE_HAS_NEXT(match) || (c = nextSkippedCodePoint(errorCode)) < 0) {
                return ce32;
            }
            if(skipped != NULL && !skipped->isEmpty()) { skipped->saveTrieState(suffixes); }
            sinceMatch = 1;
        } else if(match == USTRINGTRIE_NO_MATCH || (nextCp = nextSkippedCodePoint(errorCode)) < 0) {


            if((contractionCE32 & Collation::CONTRACT_TRAILING_CCC) != 0 &&


                    ((contractionCE32 & Collation::CONTRACT_SINGLE_CP_NO_MATCH) == 0 ||
                        sinceMatch < lookAhead)) {


                if(sinceMatch > 1) {


                    backwardNumSkipped(sinceMatch, errorCode);
                    c = nextSkippedCodePoint(errorCode);
                    lookAhead -= sinceMatch - 1;
                    sinceMatch = 1;
                }
                if(d->getFCD16(c) > 0xff) {
                    return nextCE32FromDiscontiguousContraction(
                        d, suffixes, ce32, lookAhead, c, errorCode);
                }
            }
            break;
        } else {


            c = nextCp;
            ++sinceMatch;
        }
        ++lookAhead;
        match = suffixes.nextForCodePoint(c);
    }
    backwardNumSkipped(sinceMatch, errorCode);
    return ce32;
}
