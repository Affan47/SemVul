spatial_compensation_10(uint8_t *src , uint8_t *dst, int linesize){
    int x,y;

    for(y=0;y<8;y++){
        for(x=0;x<8;x++){
            dst[x]=(src[area2+7-y]*(8-x)+src[area4+x]*x+4)>>3;
        }
        dst+=linesize;
    }
}
