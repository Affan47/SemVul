gendotquad(char *dst, uint32_t ip)
{
    int part;
    int i = 0, j;
    char temp[4];
    char *p = dst;

    for (; i < 4; i++) {
        j = 0;
        part = ip & 0xff;
        do {
            temp[j++] = (part % 10) + '0';
        }while(part /= 10);
        for (; j > 0; j--)
            *p++ = temp[j-1];
        *p++ = '.';

        ip >>= 8;
    }

    *(--p) = 0;

    return p - dst;
}
