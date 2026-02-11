_decompose(uint32_t norm32, int32_t &length,
           uint8_t &cc, uint8_t &trailCC) {
    const UChar *p=(const UChar *)_getExtraData(norm32);
    length=*p++;

    if(length&_NORM_DECOMP_FLAG_LENGTH_HAS_CC) {

        UChar bothCCs=*p++;
        cc=(uint8_t)(bothCCs>>8);
        trailCC=(uint8_t)bothCCs;
    } else {

        cc=trailCC=0;
    }

    length&=_NORM_DECOMP_LENGTH_MASK;
    return p;
}
