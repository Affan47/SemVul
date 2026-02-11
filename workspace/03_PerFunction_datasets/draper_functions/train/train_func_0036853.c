lutil_SHA1End( lutil_SHA1_CTX *ctx, char *buf )
{
    int i;
    char *p = buf;
    unsigned char digest[20];
    static const char hex[]="0123456789abcdef";

    if (p == NULL && (p = malloc(41)) == NULL)
	return 0;

    lutil_SHA1Final(digest,ctx);
    for (i = 0; i < 20; i++) {
	p[i + i] = hex[digest[i] >> 4];
	p[i + i + 1] = hex[digest[i] & 0x0f];
    }
    p[i + i] = '\0';
    return(p);
}
