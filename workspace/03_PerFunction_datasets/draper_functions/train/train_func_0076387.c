JimStrCopyUpperLower(char *dest, const char *str, int uc)
{
    while (*str) {
        int c;
        str += utf8_tounicode(str, &c);
        dest += utf8_fromunicode(dest, uc ? utf8_upper(c) : utf8_lower(c));
    }
    *dest = 0;
}
