RTC(REAL x){
    int ret=int(x*255);
    if (ret<0)
        ret=0;
    if (ret>255)
        ret=255;
    return ret;
}
