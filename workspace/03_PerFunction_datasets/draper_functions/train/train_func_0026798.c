ff_mpeg4_get_video_packet_prefix_length(MpegEncContext *s){
    switch(s->pict_type){
        case FF_I_TYPE:
            return 16;
        case FF_P_TYPE:
        case FF_S_TYPE:
            return s->f_code+15;
        case FF_B_TYPE:
            return FFMAX3(s->f_code, s->b_code, 2) + 15;
        default:
            return -1;
    }
}
