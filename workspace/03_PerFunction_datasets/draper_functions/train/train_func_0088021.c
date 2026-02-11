copy_prog(const char **prog)
{
    unsigned int len;
    unsigned int i;
    const char **p;
    char **cp;

    for(len = 0, p = prog; *p != NULL; p++, len++);
    cp = av_malloc(sizeof(*cp) * (len + 1));
    for(i = 0; i < len; i++)
        cp[i] = av_strdup(prog[i]);

    cp[len] = NULL;
    return cp;
}
