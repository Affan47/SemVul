to_ushort(unsigned char *buf,unsigned short byteorder)
{
    unsigned short value = 0;

    if(buf)
    {
        value = *(unsigned short *)buf;
#ifdef NATIVE_BYTEORDER_BIGENDIAN
        if(byteorder == TIFF_INTEL)
            value = (buf[1] << 8) | buf[0];
#else
        if(byteorder == TIFF_MOTOROLA)
            value = (buf[0] << 8) | buf[1];
#endif
    }
    return(value);
}
