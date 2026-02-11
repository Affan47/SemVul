nextSegment(UErrorCode &errorCode) {
    if(U_FAILURE(errorCode)) { return FALSE; }
    U_ASSERT(state == ITER_CHECK_FWD);

    pos = iter.getIndex(&iter, UITER_CURRENT);

    UnicodeString s;
    uint8_t prevCC = 0;
    for(;;) {

        UChar32 c = uiter_next32(&iter);
        if(c < 0) { break; }
        uint16_t fcd16 = nfcImpl.getFCD16(c);
        uint8_t leadCC = (uint8_t)(fcd16 >> 8);
        if(leadCC == 0 && !s.isEmpty()) {

            uiter_previous32(&iter);
            break;
        }
        s.append(c);
        if(leadCC != 0 && (prevCC > leadCC || CollationFCD::isFCD16OfTibetanCompositeVowel(fcd16))) {

            for(;;) {
                c = uiter_next32(&iter);
                if(c < 0) { break; }
                if(nfcImpl.getFCD16(c) <= 0xff) {
                    uiter_previous32(&iter);
                    break;
                }
                s.append(c);
            }
            if(!normalize(s, errorCode)) { return FALSE; }
            start = pos;
            limit = pos + s.length();
            state = IN_NORM_ITER_AT_LIMIT;
            pos = 0;
            return TRUE;
        }
        prevCC = (uint8_t)fcd16;
        if(prevCC == 0) {

            break;
        }
    }
    limit = pos + s.length();
    U_ASSERT(pos != limit);
    iter.move(&iter, -s.length(), UITER_CURRENT);
    state = ITER_IN_FCD_SEGMENT;
    return TRUE;
}
