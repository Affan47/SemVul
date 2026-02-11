getTrailCCFromCompYesAndZeroCC(const UChar *cpStart, const UChar *cpLimit) const {
    UChar32 c;
    if(cpStart==(cpLimit-1)) {
        c=*cpStart;
    } else {
        c=U16_GET_SUPPLEMENTARY(cpStart[0], cpStart[1]);
    }
    uint16_t prevNorm16=getNorm16(c);
    if(prevNorm16<=minYesNo) {
        return 0;
    } else {
        return (uint8_t)(*getMapping(prevNorm16)>>8);
    }
}
