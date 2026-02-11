append(const UChar *s, int32_t length,
                               uint8_t leadCC, uint8_t trailCC,
                               UErrorCode &errorCode) {
    if(length==0) {
        return TRUE;
    }
    if(remainingCapacity<length && !resize(length, errorCode)) {
        return FALSE;
    }
    remainingCapacity-=length;
    if(lastCC<=leadCC || leadCC==0) {
        if(trailCC<=1) {
            reorderStart=limit+length;
        } else if(leadCC<=1) {
            reorderStart=limit+1;
        }
        const UChar *sLimit=s+length;
        do { *limit++=*s++; } while(s!=sLimit);
        lastCC=trailCC;
    } else {
        int32_t i=0;
        UChar32 c;
        U16_NEXT(s, i, length, c);
        insert(c, leadCC);
        while(i<length) {
            U16_NEXT(s, i, length, c);
            if(i<length) {

                leadCC=Normalizer2Impl::getCCFromYesOrMaybe(impl.getNorm16(c));
            } else {
                leadCC=trailCC;
            }
            append(c, leadCC, errorCode);
        }
    }
    return TRUE;
}
