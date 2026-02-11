utf8_nextCharSafeBodyTerminated(const uint8_t **ps, UChar32 c) {
    const uint8_t *s=*ps;
    uint8_t trail, illegal=0;
    uint8_t count=U8_COUNT_TRAIL_BYTES(c);
    U_ASSERT(count<6);
    U8_MASK_LEAD_BYTE((c), count);

    switch(count) {

    case 5:
    case 4:

        illegal=1;
        break;
    case 3:
        trail=(uint8_t)(*s++ - 0x80);
        c=(c<<6)|trail;
        if(trail>0x3f || c>=0x110) {

            illegal=1;
            break;
        }
    case 2:
        trail=(uint8_t)(*s++ - 0x80);
        if(trail>0x3f) {

            illegal=1;
            break;
        }
        c=(c<<6)|trail;
    case 1:
        trail=(uint8_t)(*s++ - 0x80);
        if(trail>0x3f) {

            illegal=1;
        }
        c=(c<<6)|trail;
        break;
    case 0:
        return U_SENTINEL;

    }


    if(illegal || c<utf8_minLegal[count] || U_IS_SURROGATE(c)) {


        s=*ps;
        while(count>0 && U8_IS_TRAIL(*s)) {
            ++s;
            --count;
        }
        c=U_SENTINEL;
    }
    *ps=s;
    return c;
}
