pred8x8_left_dc_c(uint8_t *src, int stride){
    int i;
    int dc0, dc2;

    dc0=dc2=0;
    for(i=0;i<4; i++){
        dc0+= src[-1+i*stride];
        dc2+= src[-1+(i+4)*stride];
    }
    dc0= 0x01010101*((dc0 + 2)>>2);
    dc2= 0x01010101*((dc2 + 2)>>2);

    for(i=0; i<4; i++){
        ((uint32_t*)(src+i*stride))[0]=
        ((uint32_t*)(src+i*stride))[1]= dc0;
    }
    for(i=4; i<8; i++){
        ((uint32_t*)(src+i*stride))[0]=
        ((uint32_t*)(src+i*stride))[1]= dc2;
    }
}
