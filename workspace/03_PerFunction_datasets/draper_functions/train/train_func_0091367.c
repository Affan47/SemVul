decompose(UChar32 c, uint16_t norm16,
                                 ReorderingBuffer &buffer,
                                 UErrorCode &errorCode) const {

    for(;;) {

        if(isDecompYes(norm16)) {

            return buffer.append(c, getCCFromYesOrMaybe(norm16), errorCode);
        } else if(isHangul(norm16)) {

            UChar jamos[3];
            return buffer.appendZeroCC(jamos, jamos+Hangul::decompose(c, jamos), errorCode);
        } else if(isDecompNoAlgorithmic(norm16)) {
            c=mapAlgorithmic(c, norm16);
            norm16=getNorm16(c);
        } else {

            const uint16_t *mapping=getMapping(norm16);
            uint16_t firstUnit=*mapping++;
            int32_t length=firstUnit&MAPPING_LENGTH_MASK;
            uint8_t leadCC, trailCC;
            trailCC=(uint8_t)(firstUnit>>8);
            if(firstUnit&MAPPING_HAS_CCC_LCCC_WORD) {
                leadCC=(uint8_t)(*mapping++>>8);
            } else {
                leadCC=0;
            }
            return buffer.append((const UChar *)mapping, length, leadCC, trailCC, errorCode);
        }
    }
}
