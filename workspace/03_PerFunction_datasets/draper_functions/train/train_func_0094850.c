echo_command(string_list_ty *wlp)
{
    static string_ty *echo;
    string_ty       *tmp;
    char            *cp;

    if (!echo)
        echo = str_from_c("echo");
    if (wlp->nstrings < 1 || !str_equal(wlp->string[0], echo))
        return 0;
    tmp = wl2str(wlp, 0, wlp->nstrings - 1, (char *)0);
    for (cp = tmp->str_text; *cp; ++cp)
    {
        if (strchr("^|>", *cp))
        {
            str_free(tmp);
            return 0;
        }
    }
    str_free(tmp);
    return 1;
}
