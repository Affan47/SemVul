memiofread(void *chan, char *buf, int bufsize)
{
    const char *ptr;
    char *optr;
    char c;
    int l;
    rdr_t *s;

    if (bufsize == 0) return 0;
    s = (rdr_t *) chan;
    if (s->cur >= s->len)
        return 0;
    l = 0;
    ptr = s->data + s->cur;
    optr = buf;

    c = *ptr++;
    do {
        *optr++ = c;
        l++;


    } while ((c != '\n') && (l < bufsize) && (c = *ptr++));
    s->cur += l;
    return l;
}
