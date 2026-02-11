gcide_escape_to_utf8(const char *esc)
{
    char const *s = gcide_webchr[xnum(esc[0]) * 16 + xnum(esc[1])];
    return s[0] ? s : NULL;
}
