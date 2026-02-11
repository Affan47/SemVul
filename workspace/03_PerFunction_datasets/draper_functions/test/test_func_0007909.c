SITEcopystrings(char **av)
{
    char	**new;
    char	**pp;
    char	**save;

    for (pp = av; *pp; pp++)
	continue;
    for (new = save = xmalloc((pp - av + 1) * sizeof(char *)), pp = av; *pp; pp++)
	*new++ = xstrdup(*pp);
    *new = NULL;
    return save;
}
