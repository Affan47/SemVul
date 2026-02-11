ucs4_isspace(UCS c)
{
    return((c < 0xff && isspace((unsigned char) c)) || SPECIAL_SPACE(c));
}
