hashstring(const char *str, char *result, int maxlen)
{
    tiger::hashval hv;
    if(maxlen < 2*(int)sizeof(hv.bytes) + 1) return false;
    tiger::hash((uchar *)str, strlen(str), hv);
    loopi(sizeof(hv.bytes))
    {
        uchar c = hv.bytes[i];
        *result++ = "0123456789abcdef"[c&0xF];
        *result++ = "0123456789abcdef"[c>>4];
    }
    *result = '\0';
    return true;
}
