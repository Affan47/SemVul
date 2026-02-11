rsvg_css_parse_overflow (const char *str, gboolean * inherit)
{
    SETINHERIT ();
    if (!strcmp (str, "visible") || !strcmp (str, "auto"))
        return 1;
    if (!strcmp (str, "hidden") || !strcmp (str, "scroll"))
        return 0;
    UNSETINHERIT ();
    return 0;
}
