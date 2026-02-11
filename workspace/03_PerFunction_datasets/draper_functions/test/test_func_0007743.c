append_str(char *buf, const char *new_str)
{
    int space_left;

    if (strstri(buf, new_str)) return 0;

    space_left = BUFSZ - strlen(buf) - 1;
    strncat(buf, " or ", space_left);
    strncat(buf, new_str, space_left - 4);
    return 1;
}
