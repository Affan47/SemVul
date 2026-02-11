nextChar(const HB_UChar16 *str, hb_uint32 len, hb_uint32 pos)
{
    const HB_UChar16 *ch = str + pos + 1;
    pos++;
    while(pos < len) {

        if(HB_GetUnicodeCharCategory(*ch) != HB_Mark_NonSpacing)
            return *ch;

        pos++;
        ch++;
    }
    return ReplacementCharacter;
}
