pred16x16_top_dc_c(uint8_t *src, int stride){
    int i, dc=0;

    for(i=0;i<16; i++){
        dc+= src[i-stride];
    }
    dc= 0x01010101*((dc + 8)>>4);

    for(i=0; i<16; i++){
        ((uint32_t*)(src+i*stride))[0]=
        ((uint32_t*)(src+i*stride))[1]=
        ((uint32_t*)(src+i*stride))[2]=
        ((uint32_t*)(src+i*stride))[3]= dc;
    }
}
