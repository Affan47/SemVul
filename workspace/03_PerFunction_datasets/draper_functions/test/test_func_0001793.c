sal_to_bool(s)
    char_u	*s;
{
    return STRCMP(s, "1") == 0 || STRCMP(s, "true") == 0;
}
