firstL_R_AL_EN_AN(UBiDi *pBiDi) {
    const UChar *text=pBiDi->epilogue;
    int32_t length=pBiDi->epiLength;
    int32_t i;
    UChar32 uchar;
    DirProp dirProp;
    for(i=0; i<length; ) {

        U16_NEXT(text, i, length, uchar);
        dirProp=(DirProp)ubidi_getCustomizedClass(pBiDi, uchar);
        if(dirProp==L) {
            return DirProp_L;
        }
        if(dirProp==R || dirProp==AL) {
            return DirProp_R;
        }
        if(dirProp==EN) {
            return DirProp_EN;
        }
        if(dirProp==AN) {
            return DirProp_AN;
        }
    }
    return DirProp_ON;
}
