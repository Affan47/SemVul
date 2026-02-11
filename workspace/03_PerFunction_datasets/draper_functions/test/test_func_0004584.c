gxf_parse_mpeg_frame(GXFStreamContext *sc, const uint8_t *buf, int size)
{
    uint32_t c=-1;
    int i;
    for(i=0; i<size-4 && c!=0x100; i++){
        c = (c<<8) + buf[i];
        if(c == 0x1B8 && sc->first_gop_closed == -1)
            sc->first_gop_closed= (buf[i+4]>>6)&1;
    }
    return (buf[i+1]>>3)&7;
}
