parse_keysym_file (const gchar *keysym_file)
{
    gchar *contents = NULL;
    gchar **lines = NULL;
    gsize length = 0;
    GError *error = NULL;
    GHashTable *table = NULL;
    int i;

    if (!g_file_get_contents (keysym_file, &contents, &length, &error)) {
        g_error ("Specify $IBUS_KEYSYMS for the path of ibuskeysyms.h: %s",
                 error->message);
        g_error_free (error);
    }

    table = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);

    lines = g_strsplit (contents, "\n", -1);
    g_free (contents);

    for (i = 0; lines[i] != NULL; i++) {
        const gchar *line = lines[i];
        gchar **words;
        gint length;
        const gchar *key;
        gint64 code;

        if (!g_str_has_prefix (line, "#define"))
            continue;

        words = g_strsplit (line , " ", -1);
        length = g_strv_length (words);

        g_assert (length >= 2);

        key = words[1];


        if (length == 2) {
            g_assert (!g_str_has_prefix (key, "IBUS_KEY"));
            continue;
        }

        code = g_ascii_strtoll (words[2], NULL, 16);
        g_hash_table_insert (table, g_strdup (key), GINT_TO_POINTER (code));
        g_strfreev (words);
    }

    g_strfreev (lines);
    return table;
}
