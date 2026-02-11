is_str_empty(const gchar *str) {
    guint8 i;
    gboolean ret = TRUE;

    if ((str == NULL) || (*str == 0))
        return TRUE;

    for (i = 0; i < strlen (str); i++)
        if (!g_ascii_isspace (str[i])) {
           ret = FALSE;

           break;
        }

    return ret;
}
