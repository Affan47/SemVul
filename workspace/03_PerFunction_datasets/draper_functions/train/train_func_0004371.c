zipPrevDecodeLength(unsigned char *p, unsigned int *lensize) {
    unsigned int len = *p;
    if (len < ZIP_BIGLEN) {
        if (lensize) *lensize = 1;
    } else {
        if (lensize) *lensize = 1+sizeof(len);
        memcpy(&len,p+1,sizeof(len));
    }
    return len;
}
