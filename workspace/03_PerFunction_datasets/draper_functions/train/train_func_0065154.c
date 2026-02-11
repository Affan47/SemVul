globexp1(const Char * pattern, glob_t * pglob, int recursion)
{
    const Char *ptr = pattern;
    int rv = 0;

    if (pglob->gl_maxdepth > 0 && recursion > pglob->gl_maxdepth) {
        errno = 0;
        return 0;
    }

    if (pattern[0] == LBRACE && pattern[1] == RBRACE && pattern[2] == EOS)
        return glob0(pattern, pglob);

    while ((ptr =
            (const Char *) g_strchr((const Char *) ptr, LBRACE)) != NULL) {
        if (!globexp2(ptr, pattern, pglob, &rv, recursion + 1))
            return rv;
    }

    return glob0(pattern, pglob);
}
