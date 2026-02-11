netsnmp_addrstr_hton(char *ptr, size_t len)
{
#ifndef WORDS_BIGENDIAN
    char tmp[8];

    if (8 == len) {
        tmp[0] = ptr[6];
        tmp[1] = ptr[7];
        tmp[2] = ptr[4];
        tmp[3] = ptr[5];
        tmp[4] = ptr[2];
        tmp[5] = ptr[3];
        tmp[6] = ptr[0];
        tmp[7] = ptr[1];
        memcpy (ptr, &tmp, 8);
    }
    else if (32 == len) {
        netsnmp_addrstr_hton(ptr   , 8);
        netsnmp_addrstr_hton(ptr+8 , 8);
        netsnmp_addrstr_hton(ptr+16, 8);
        netsnmp_addrstr_hton(ptr+24, 8);
    }
    else
        return -1;
#endif

    return 0;
}
