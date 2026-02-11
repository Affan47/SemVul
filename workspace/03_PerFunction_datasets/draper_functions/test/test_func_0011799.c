_findNextStarter(const UChar *src, const UChar *limit,
                 uint32_t qcMask, uint32_t decompQCMask, UChar minNoMaybe) {
    const UChar *p;
    uint32_t norm32, ccOrQCMask;
    int32_t length;
    UChar c, c2;
    uint8_t cc, trailCC;

    ccOrQCMask=_NORM_CC_MASK|qcMask;

    for(;;) {
        if(src==limit) {
            break;
        }
        c=*src;
        if(c<minNoMaybe) {
            break;
        }

        norm32=_getNorm32(c);
        if((norm32&ccOrQCMask)==0) {
            break;
        }

        if(U16_IS_LEAD(c)) {

            if((src+1)==limit || !U16_IS_TRAIL(c2=*(src+1))) {
                break;
            }
            norm32=_getNorm32FromSurrogatePair(c, c2);

            if((norm32&ccOrQCMask)==0) {
                break;
            }
        } else {
            c2=0;
        }


        if(norm32&decompQCMask) {

            p=_decompose(norm32, decompQCMask, length, cc, trailCC);


            if(cc==0 && (_getNorm32(p, qcMask)&qcMask)==0) {
                break;
            }
        }

        src+= c2==0 ? 1 : 2;
    }

    return src;
}
