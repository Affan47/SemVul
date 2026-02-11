previousSegment(UErrorCode &errorCode) {
    if(U_FAILURE(errorCode)) { return FALSE; }
    U_ASSERT(state == ITER_CHECK_BWD);

    pos = iter.getIndex(&iter, UITER_CURRENT);

    UnicodeString s;
    uint8_t nextCC = 0;
    for(;;) {

        UChar32 c = uiter_previous32(&iter);
        if(c < 0) { break; }
        uint16_t fcd16 = nfcImpl.getFCD16(c);
        uint8_t trailCC = (uint8_t)fcd16;
        if(trailCC == 0 && !s.isEmpty()) {

            uiter_next32(&iter);
            break;
        }
        s.append(c);
        if(trailCC != 0 && ((nextCC != 0 && trailCC > nextCC) ||
                            CollationFCD::isFCD16OfTibetanCompositeVowel(fcd16))) {

            while(fcd16 > 0xff) {
                c = uiter_previous32(&iter);
                if(c < 0) { break; }
                fcd16 = nfcImpl.getFCD16(c);
                if(fcd16 == 0) {
                    (void)uiter_next32(&iter);
                    break;
                }
                s.append(c);
            }
            s.reverse();
            if(!normalize(s, errorCode)) { return FALSE; }
            limit = pos;
            start = pos - s.length();
            state = IN_NORM_ITER_AT_START;
            pos = normalized.length();
            return TRUE;
        }
        nextCC = (uint8_t)(fcd16 >> 8);
        if(nextCC == 0) {

            break;
        }
    }
    start = pos - s.length();
    U_ASSERT(pos != start);
    iter.move(&iter, s.length(), UITER_CURRENT);
    state = ITER_IN_FCD_SEGMENT;
    return TRUE;
}
