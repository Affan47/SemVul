os_legal_path(string_ty *str)
{
    char            *s;
    char            *ep;
    size_t          max;

    max = os_pathconf_path_max(".");
    if (str->str_length < 1 || str->str_length > max)
        return 0;
    max = os_pathconf_name_max(".");
    s = str->str_text;
    for (;;)
    {
        ep = strchr(s, '/');
        if (!ep)
            return (strlen(s) <= max);
        if ((size_t) (ep - s) > max)
            return 0;
        s = ep + 1;
    }
}
