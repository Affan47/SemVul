exeext(const char *s)
{
    int             n;
    const char      *suffix;
    int             result;

    for (n = 0;; ++n)
    {
        suffix = exeext_nth(n);
        if (!suffix || !*suffix)
            return -1;
        result = look_for_suffix(s, suffix);
        if (result >= 0)
            return result;
    }
}
