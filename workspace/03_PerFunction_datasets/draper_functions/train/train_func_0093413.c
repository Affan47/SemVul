check(void *_desc, int len, unsigned type, int size)
{
    unsigned char *desc = _desc;

    if(len < size) return -1;
    if(desc[0] < size) return -1;
    if(desc[0] > len) return -1;
    if(desc[1] != type) return -1;

    return 0;
}
