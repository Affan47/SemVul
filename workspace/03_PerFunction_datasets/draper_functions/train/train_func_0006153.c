check_utf8(const gchar *string,
           GQuark key,
           GSList **errors)
{
    const gchar *end;

    if (G_LIKELY(g_utf8_validate(string, -1, &end)))
        return TRUE;

    *errors = g_slist_prepend(*errors,
                              FAIL(GWY_DATA_ERROR_NON_UTF8_STRING, key,
                                   _("byte at position %d"),
                                   end - string));
    return FALSE;
}
