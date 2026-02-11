seahorse_util_string_trim_whitespace (gchar *text)
{
    gchar *b, *e, *n;

    g_assert (text);
    g_assert (g_utf8_validate (text, -1, NULL));


    b = text;
    while (*b && g_unichar_isspace (g_utf8_get_char (b)))
        b = g_utf8_next_char (b);


    n = e = b + strlen (b);
    while (n >= b) {
        if (*n && !g_unichar_isspace (g_utf8_get_char (n)))
            break;
        e = n;
        n = g_utf8_prev_char (e);
    }

    g_assert (b >= text);
    g_assert (e >= b);

    *e = 0;
    g_memmove (text, b, (e + 1) - b);
}
