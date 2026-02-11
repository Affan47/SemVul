mbstowcs_dbcs_decompose( const struct dbcs_table *table,
                                    const unsigned char *src, unsigned int srclen,
                                    WCHAR *dst, unsigned int dstlen )
{
    const WCHAR * const cp2uni = table->cp2uni;
    const unsigned char * const cp2uni_lb = table->cp2uni_leadbytes;
    unsigned int len;
    WCHAR ch;
    int res;

    if (!dstlen)
    {
        WCHAR dummy[4];
        for (len = 0; srclen; srclen--, src++)
        {
            unsigned char off = cp2uni_lb[*src];
            if (off)
            {
                if (!--srclen) break;
                src++;
                ch = cp2uni[(off << 8) + *src];
            }
            else ch = cp2uni[*src];
            len += get_decomposition( ch, dummy, 4 );
        }
        return len;
    }

    for (len = dstlen; srclen && len; srclen--, src++)
    {
        unsigned char off = cp2uni_lb[*src];
        if (off)
        {
            if (!--srclen) break;
            src++;
            ch = cp2uni[(off << 8) + *src];
        }
        else ch = cp2uni[*src];
        if (!(res = get_decomposition( ch, dst, len ))) break;
        dst += res;
        len -= res;
    }
    if (srclen) return -1;
    return dstlen - len;
}
