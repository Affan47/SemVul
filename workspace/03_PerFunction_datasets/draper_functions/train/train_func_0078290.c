checkExplicitLevels(UBiDi *pBiDi, UErrorCode *pErrorCode) {
    const DirProp *dirProps=pBiDi->dirProps;
    DirProp dirProp;
    UBiDiLevel *levels=pBiDi->levels;
    const UChar *text=pBiDi->text;

    int32_t i, length=pBiDi->length;
    Flags flags=0;
    UBiDiLevel level;
    uint32_t paraIndex=0;

    for(i=0; i<length; ++i) {
        level=levels[i];
        dirProp=NO_CONTEXT_RTL(dirProps[i]);
        if(level&UBIDI_LEVEL_OVERRIDE) {

            level&=~UBIDI_LEVEL_OVERRIDE;
            flags|=DIRPROP_FLAG_O(level);
        } else {

            flags|=DIRPROP_FLAG_E(level)|DIRPROP_FLAG(dirProp);
        }
        if((level<GET_PARALEVEL(pBiDi, i) &&
            !((0==level)&&(dirProp==B))) ||
           (UBIDI_MAX_EXPLICIT_LEVEL<level)) {

            *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
            return UBIDI_LTR;
        }
        if((dirProp==B) && ((i+1)<length)) {
            if(!((text[i]==CR) && (text[i+1]==LF))) {
                pBiDi->paras[paraIndex++]=i+1;
            }
        }
    }
    if(flags&MASK_EMBEDDING) {
        flags|=DIRPROP_FLAG_LR(pBiDi->paraLevel);
    }


    pBiDi->flags=flags;
    return directionFromFlags(pBiDi);
}
