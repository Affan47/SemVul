gnc_html_unescape_newlines(const gchar * in)
{
    const char * ip = in;
    char    * cstr = NULL;
    GString * rv = g_string_new("");

    for (ip = in; *ip; ip++)
    {
        if ((*ip == '\\') && (*(ip + 1) == 'n'))
        {
            g_string_append(rv, "\n");
            ip++;
        }
        else
        {
            g_string_append_c(rv, *ip);
        }
    }

    g_string_append_c(rv, 0);
    cstr = rv->str;
    g_string_free(rv, FALSE);
    return cstr;
}
