k5_base64_encode(const void *data, size_t len)
{
    char *s, *p;
    size_t i;
    unsigned int c;
    const unsigned char *q;

    if (len > SIZE_MAX / 4)
        return NULL;

    p = s = malloc(len * 4 / 3 + 4);
    if (p == NULL)
        return NULL;
    q = (const unsigned char *)data;

    for (i = 0; i < len;) {
        c = q[i++];
        c *= 256;
        if (i < len)
            c += q[i];
        i++;
        c *= 256;
        if (i < len)
            c += q[i];
        i++;
        p[0] = base64_chars[(c & 0x00fc0000) >> 18];
        p[1] = base64_chars[(c & 0x0003f000) >> 12];
        p[2] = base64_chars[(c & 0x00000fc0) >> 6];
        p[3] = base64_chars[(c & 0x0000003f) >> 0];
        if (i > len)
            p[3] = '=';
        if (i > len + 1)
            p[2] = '=';
        p += 4;
    }
    *p = '\0';
    return s;
}
