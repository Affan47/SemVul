hasDecompBoundary(UChar32 c, UBool before) const {
    for(;;) {
        if(c<minDecompNoCP) {
            return TRUE;
        }
        uint16_t norm16=getNorm16(c);
        if(isHangul(norm16) || isDecompYesAndZeroCC(norm16)) {
            return TRUE;
        } else if(norm16>MIN_NORMAL_MAYBE_YES) {
            return FALSE;
        } else if(isDecompNoAlgorithmic(norm16)) {
            c=mapAlgorithmic(c, norm16);
        } else {

            const uint16_t *mapping=getMapping(norm16);
            uint16_t firstUnit=*mapping++;
            if((firstUnit&MAPPING_LENGTH_MASK)==0) {
                return FALSE;
            }
            if(!before) {


                if(firstUnit>0x1ff) {
                    return FALSE;
                }
                if(firstUnit<=0xff) {
                    return TRUE;
                }

            }

            return (firstUnit&MAPPING_HAS_CCC_LCCC_WORD)==0 || (*mapping&0xff00)==0;
        }
    }
}
