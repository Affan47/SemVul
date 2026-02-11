prefs_get_double_value(const gchar *key, gdouble *value) {
    gchar *string;
    gboolean valid = FALSE;

    lock_prefs_table();

    g_return_val_if_fail (prefs_table, (unlock_prefs_table(), FALSE));

    string = g_hash_table_lookup(prefs_table, key);

    if (value) {
        if (string)
            *value = g_ascii_strtod(string, NULL);
        else
            *value = 0;
    }

    if (string)
        valid = TRUE;

    unlock_prefs_table();

    return valid;
}
