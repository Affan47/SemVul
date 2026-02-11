vc1_split(AVCodecContext *avctx,
                           const uint8_t *buf, int buf_size)
{
    int i;
    uint32_t state= -1;
    int charged=0;

    for(i=0; i<buf_size; i++){
        state= (state<<8) | buf[i];
        if(IS_MARKER(state)){
            if(state == VC1_CODE_SEQHDR || state == VC1_CODE_ENTRYPOINT){
                charged=1;
            }else if(charged){
                return i-3;
            }
        }
    }
    return 0;
}
