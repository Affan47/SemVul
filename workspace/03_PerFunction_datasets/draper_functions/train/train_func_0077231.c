directionFromFlags(UBiDi *pBiDi) {
    Flags flags=pBiDi->flags;

    if(!(flags&MASK_RTL || ((flags&DIRPROP_FLAG(AN)) && (flags&MASK_POSSIBLE_N)))) {
        return UBIDI_LTR;
    } else if(!(flags&MASK_LTR)) {
        return UBIDI_RTL;
    } else {
        return UBIDI_MIXED;
    }
}
