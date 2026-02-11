zipTryEncoding(unsigned char *entry, unsigned int entrylen, long long *v, unsigned char *encoding) {
    long long value;
    char *eptr;
    char buf[32];

    if (entrylen >= 32 || entrylen == 0) return 0;
    if (entry[0] == '-' || (entry[0] >= '0' && entry[0] <= '9')) {
        int slen;


        memcpy(buf,entry,entrylen);
        buf[entrylen] = '\0';
        value = strtoll(buf,&eptr,10);
        if (eptr[0] != '\0') return 0;
        slen = ll2string(buf,32,value);
        if (entrylen != (unsigned)slen || memcmp(buf,entry,slen)) return 0;


        if (value >= INT16_MIN && value <= INT16_MAX) {
            *encoding = ZIP_INT_16B;
        } else if (value >= INT32_MIN && value <= INT32_MAX) {
            *encoding = ZIP_INT_32B;
        } else {
            *encoding = ZIP_INT_64B;
        }
        *v = value;
        return 1;
    }
    return 0;
}
