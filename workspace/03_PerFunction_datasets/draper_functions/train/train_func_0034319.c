cryptui_key_get_base (const gchar *key)
{
    gchar *ch;


    ch = strchr (key, ':');
    if (ch) {
        ch = strchr (ch + 1, ':');
        if (ch)
            return g_strndup (key, ch - key);
    }


    return g_strdup (key);
}
