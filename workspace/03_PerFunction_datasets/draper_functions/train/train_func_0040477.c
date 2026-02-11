u_toSmallKana(const UChar *source, const uint32_t sourceLen, UChar *resBuf, const uint32_t resLen, UErrorCode *status) {
    uint32_t i = 0;
    UChar c;

    if(U_FAILURE(*status)) {
        return 0;
    }

    if(sourceLen > resLen) {
        *status = U_MEMORY_ALLOCATION_ERROR;
        return 0;
    }

    for(i = 0; i < sourceLen; i++) {
        c = source[i];
        if(0x3041 <= c && c <= 0x30FA) {
            switch(c - 0x3000) {
            case 0x42: case 0x44: case 0x46: case 0x48: case 0x4A: case 0x64: case 0x84: case 0x86: case 0x8F:
            case 0xA2: case 0xA4: case 0xA6: case 0xA8: case 0xAA: case 0xC4: case 0xE4: case 0xE6: case 0xEF:
                c--;
                break;
            case 0xAB:
                c = 0x30F5;
                break;
            case 0xB1:
                c = 0x30F6;
                break;
            }
        }
        resBuf[i] = c;
    }
    return sourceLen;
}
