copy_string(char *s)
{
    char    *cp;

    errno = 0;
    cp = malloc(strlen(s) + 1);
    if (!cp)
    {
        if (!errno)
            errno = ENOMEM;
        double_jeopardy();
    }
    strcpy(cp, s);
    return cp;
}
