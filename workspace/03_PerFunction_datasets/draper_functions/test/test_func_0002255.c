setHaveSeenString(const uint32_t *s, int32_t length) {
    uint32_t c;

    while(length>0) {
        c=*s++;
        haveSeenFlags[(c>>5)&0xff]|=(1<<(c&0x1f));
        --length;
    }
}
