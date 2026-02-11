uhash_compareTokens(const UHashTok key1, const UHashTok key2)
{


    UColToken *p1 = (UColToken *)key1.pointer;
    UColToken *p2 = (UColToken *)key2.pointer;
    const UChar *s1 = (p1->source & 0x00FFFFFF) + *(p1->rulesToParseHdl);
    const UChar *s2 = (p2->source & 0x00FFFFFF) + *(p2->rulesToParseHdl);
    uint32_t s1L = ((p1->source & 0xFF000000) >> 24);
    uint32_t s2L = ((p2->source & 0xFF000000) >> 24);
    const UChar *end = s1+s1L-1;

    if (p1 == p2) {
        return TRUE;
    }
    if (p1->source == 0 || p2->source == 0) {
        return FALSE;
    }
    if(s1L != s2L) {
        return FALSE;
    }
    if(p1->source == p2->source) {
        return TRUE;
    }
    while((s1 < end) && *s1 == *s2) {
        ++s1;
        ++s2;
    }
    if(*s1 == *s2) {
        return TRUE;
    } else {
        return FALSE;
    }
}
