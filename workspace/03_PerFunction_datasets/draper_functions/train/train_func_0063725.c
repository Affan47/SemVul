writehex(char **p, ulong v, int l)
{
    int i = l * 2;
    static const char digit[] = "0123456789abcdef";

    for (; i--;)
        *((*p)++) = digit[v >> (i * 4) & 15];
}
