fname_encode(const char *legal,
             char quotechar,
             char *s, char *callerbuf,
             int bufsz)
{
    char *sp, *op;
    int cnt = 0;
    static char hexdigits[] = "0123456789ABCDEF";

    sp = s;
    op = callerbuf;
    *op = '\0';

    while (*sp)
    {

        if ((bufsz - cnt) <= 4) return callerbuf;

        if (*sp == quotechar)
        {
            sprintf(op, "%c%02X", quotechar, *sp);
            op += 3;
            cnt += 3;
        }
        else if ((index(legal, *sp) != 0) || (index(hexdigits, *sp) != 0))
        {
            *op++ = *sp;
            *op = '\0';
            cnt++;
        }
        else
        {
            sprintf(op,"%c%02X", quotechar, *sp);
            op += 3;
            cnt += 3;
        }
        sp++;
    }
    return callerbuf;
}
