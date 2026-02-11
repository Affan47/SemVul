_getNextCombining(UChar *&p, const UChar *limit,
                  UChar &c, UChar &c2,
                  uint16_t &combiningIndex, uint8_t &cc,
                  const UnicodeSet *nx) {
    uint32_t norm32, combineFlags;


    c=*p++;
    norm32=_getNorm32(c);


    c2=0;
    combiningIndex=0;
    cc=0;

    if((norm32&(_NORM_CC_MASK|_NORM_COMBINES_ANY))==0) {
        return 0;
    } else {
        if(isNorm32Regular(norm32)) {

        } else if(isNorm32HangulOrJamo(norm32)) {

            combiningIndex=(uint16_t)(0xfff0|(norm32>>_NORM_EXTRA_SHIFT));
            return norm32&_NORM_COMBINES_ANY;
        } else {

            if(p!=limit && UTF_IS_SECOND_SURROGATE(c2=*p)) {
                ++p;
                norm32=_getNorm32FromSurrogatePair(c, c2);
            } else {
                c2=0;
                return 0;
            }
        }

        if(nx_contains(nx, c, c2)) {
            return 0;
        }

        cc=(uint8_t)(norm32>>_NORM_CC_SHIFT);

        combineFlags=norm32&_NORM_COMBINES_ANY;
        if(combineFlags!=0) {
            combiningIndex=*(_getExtraData(norm32)-1);
        }
        return combineFlags;
    }
}
