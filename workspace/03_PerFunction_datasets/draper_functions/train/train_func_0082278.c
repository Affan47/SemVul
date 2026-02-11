sub_left_prediction_bgr32(HYuvContext *s, uint8_t *dst, uint8_t *src, int w, int *red, int *green, int *blue){
    int i;
    int r,g,b;
    r= *red;
    g= *green;
    b= *blue;
    for(i=0; i<FFMIN(w,4); i++){
        const int rt= src[i*4+R];
        const int gt= src[i*4+G];
        const int bt= src[i*4+B];
        dst[i*4+R]= rt - r;
        dst[i*4+G]= gt - g;
        dst[i*4+B]= bt - b;
        r = rt;
        g = gt;
        b = bt;
    }
    s->dsp.diff_bytes(dst+16, src+16, src+12, w*4-16);
    *red=   src[(w-1)*4+R];
    *green= src[(w-1)*4+G];
    *blue=  src[(w-1)*4+B];
}
