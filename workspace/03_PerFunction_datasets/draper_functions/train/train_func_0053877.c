affix_filename(const char *path, const char *prefix, const char *suffix)
{
    char *p;
    char *tmp;

    size_t pref_len, suff_len;

    pref_len = (prefix) ? strlen(prefix) : 0;
    suff_len = (suffix) ? strlen(suffix) : 0;

    p = malloc(strlen(path) + pref_len + suff_len + 1);
    if (!p)
        return NULL;


    tmp = dirname_r(path);
    if (!tmp)
    {
        free(p);
        return NULL;
    }
    strcpy(p, tmp);
    free(tmp);


    if (p[1] != '\0')
        strcat(p, "/");
    if (prefix)
        strcat(p, prefix);


    tmp = basename_r(path);
    if (!tmp)
    {
        free(p);
        return NULL;
    }
    strcat(p, tmp);
    free(tmp);


    if (suffix)
        strcat(p, suffix);

    return p;
}
