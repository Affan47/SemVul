ucol_getLatinOneContractionUTF8(const UCollator *coll, int32_t strength,
                          uint32_t CE, const char *s, int32_t *index, int32_t len)
{
    const UChar *UCharOffset = (UChar *)coll->image+getContractOffset(CE&0xFFF);
    int32_t latinOneOffset = (CE & 0x00FFF000) >> 12;
    int32_t offset = 1;
    UChar32 schar = 0, tchar = 0;

    for(;;) {
        if (*index == len) {
            return(coll->latinOneCEs[strength*coll->latinOneTableLen+latinOneOffset]);
        }
        U8_GET_OR_FFFD((const uint8_t*)s, 0, *index, len, schar);
        if (len < 0 && schar == 0) {
            return(coll->latinOneCEs[strength*coll->latinOneTableLen+latinOneOffset]);
        }

        while(schar > (tchar = *(UCharOffset+offset))) {
            offset++;
        }

        if (schar == tchar) {
            U8_FWD_1(s, *index, len);
            return(coll->latinOneCEs[strength*coll->latinOneTableLen+latinOneOffset+offset]);
        }
        else
        {
            if(schar & 0xFF00 ) {
                return UCOL_BAIL_OUT_CE;
            }

            uint32_t isZeroCE = UTRIE_GET32_FROM_LEAD(&coll->mapping, schar);
            if(isZeroCE == 0) {
                U8_FWD_1(s, *index, len);
                continue;
            }

            return(coll->latinOneCEs[strength*coll->latinOneTableLen+latinOneOffset]);
        }
    }
}
