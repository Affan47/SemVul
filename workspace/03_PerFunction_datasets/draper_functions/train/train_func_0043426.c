is_cspace(char *buf, long int *pos)
{
    if (isspace(buf[*pos]))
        return 1;
    if (buf[*pos] == '/')
    {
        if ((buf[(*pos) + 1] == '*') || (buf[(*pos) + 1] == '/'))
            return 1;
    }
    return 0;
}
