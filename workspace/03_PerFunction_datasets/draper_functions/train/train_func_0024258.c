efreet_util_glob_match(const char *str, const char *glob)
{
    if (!str || !glob)
        return 0;
    if (glob[0] == '\0')
    {
        if (str[0] == '\0') return 1;
        return 0;
    }
    if (!strcmp(glob, "*")) return 1;
    if (!fnmatch(glob, str, 0)) return 1;
    return 0;
}
