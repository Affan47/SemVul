to_ulong(unsigned char *buf,unsigned short byteorder)
{
    u_int32_t value = 0;

    if(buf)
    {
        value = *(u_int32_t *)buf;
#ifdef NATIVE_BYTEORDER_BIGENDIAN
        if(byteorder == TIFF_INTEL)
#else
        if(byteorder == TIFF_MOTOROLA)
#endif
            value = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    }
    return((unsigned long)value);
}
