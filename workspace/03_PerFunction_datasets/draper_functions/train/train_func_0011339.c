skip_space (char *s)
{
    if (!s) return NULL;

    for ( ; *s && isascii(*s) && isspace(*s); s++)
        ;
    return s;
}
