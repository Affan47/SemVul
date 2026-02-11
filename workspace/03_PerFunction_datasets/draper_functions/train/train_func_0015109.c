normalize_str_pos(const char *str, int32_t pos)
{
    if (str == NULL)
        return 0;
    if (pos >= 0)
        return strnlen(str, pos);
    pos += 1 + strlen(str);
    if (pos >= 0)
        return pos;
    return 0;
}
