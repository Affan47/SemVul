vc1_find_frame_end(ParseContext *pc, const uint8_t *buf,
                               int buf_size) {
    int pic_found, i;
    uint32_t state;

    pic_found= pc->frame_start_found;
    state= pc->state;

    i=0;
    if(!pic_found){
        for(i=0; i<buf_size; i++){
            state= (state<<8) | buf[i];
            if(state == VC1_CODE_FRAME || state == VC1_CODE_FIELD){
                i++;
                pic_found=1;
                break;
            }
        }
    }

    if(pic_found){

        if (buf_size == 0)
            return 0;
        for(; i<buf_size; i++){
            state= (state<<8) | buf[i];
            if(IS_MARKER(state) && state != VC1_CODE_FIELD && state != VC1_CODE_SLICE){
                pc->frame_start_found=0;
                pc->state=-1;
                return i-3;
            }
        }
    }
    pc->frame_start_found= pic_found;
    pc->state= state;
    return END_NOT_FOUND;
}
