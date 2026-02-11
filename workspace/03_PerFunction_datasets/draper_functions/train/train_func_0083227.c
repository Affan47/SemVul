yajl_string_scan(const unsigned char * buf, size_t len, int utf8check)
{
    unsigned char mask = IJC|NFP|(utf8check ? NUC : 0);
    size_t skip = 0;
    while (skip < len && !(charLookupTable[*buf] & mask))
    {
        skip++;
        buf++;
    }
    return skip;
}
