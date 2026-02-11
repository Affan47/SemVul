calculateSize(const UChar *source, int32_t sourceLength,
int32_t destSize,uint32_t options) {
    int32_t i = 0;

    int lamAlefOption = 0;
    int tashkeelOption = 0;

    destSize = sourceLength;

    if (((options&U_SHAPE_LETTERS_MASK) == U_SHAPE_LETTERS_SHAPE ||
        ((options&U_SHAPE_LETTERS_MASK) == U_SHAPE_LETTERS_SHAPE_TASHKEEL_ISOLATED )) &&
        ((options&U_SHAPE_LAMALEF_MASK) == U_SHAPE_LAMALEF_RESIZE )){
            lamAlefOption = 1;
    }
    if((options&U_SHAPE_LETTERS_MASK) == U_SHAPE_LETTERS_SHAPE &&
       ((options&U_SHAPE_TASHKEEL_MASK) == U_SHAPE_TASHKEEL_RESIZE ) ){
            tashkeelOption = 1;
        }

    if(lamAlefOption || tashkeelOption){
        if((options&U_SHAPE_TEXT_DIRECTION_MASK)==U_SHAPE_TEXT_DIRECTION_VISUAL_LTR) {
            for(i=0;i<sourceLength;i++) {
                if( ((isAlefChar(source[i]))&& (i<(sourceLength-1)) &&(source[i+1] == LAM_CHAR)) || (isTashkeelCharFE(source[i])) ) {
                        destSize--;
                    }
                }
            }else if((options&U_SHAPE_TEXT_DIRECTION_MASK)==U_SHAPE_TEXT_DIRECTION_LOGICAL) {
                for(i=0;i<sourceLength;i++) {
                    if( ( (source[i] == LAM_CHAR) && (i<(sourceLength-1)) && (isAlefChar(source[i+1]))) || (isTashkeelCharFE(source[i])) ) {
                        destSize--;
                    }
                }
            }
        }

    if ((options&U_SHAPE_LETTERS_MASK) == U_SHAPE_LETTERS_UNSHAPE){
        if ( (options&U_SHAPE_LAMALEF_MASK) == U_SHAPE_LAMALEF_RESIZE){
            for(i=0;i<sourceLength;i++) {
                if(isLamAlefChar(source[i]))
                destSize++;
            }
        }
    }

    return destSize;
}
