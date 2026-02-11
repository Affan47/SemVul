ios_getutf8(ios_t *s, uint32_t *pwc)
{
    int c;
    size_t sz;
    char c0;
    char buf[8];

    c = ios_getc(s);
    if (c == IOS_EOF)
        return IOS_EOF;
    c0 = (char)c;
    if ((unsigned char)c0 < 0x80) {
        *pwc = (uint32_t)(unsigned char)c0;
        return 1;
    }
    sz = u8_seqlen(&c0)-1;
    if (ios_ungetc(c, s) == IOS_EOF)
        return IOS_EOF;
    if (ios_readprep(s, sz) < sz)

        return IOS_EOF;
    size_t i = s->bpos;
    *pwc = u8_nextchar(s->buf, &i);
    ios_read(s, buf, sz+1);
    return 1;
}
