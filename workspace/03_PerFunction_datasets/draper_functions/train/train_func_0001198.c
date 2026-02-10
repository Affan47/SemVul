temp_prefs_get_double(TempPrefs *temp_prefs, const gchar *key) {
    gchar *string;
    gdouble value;

    g_return_val_if_fail (temp_prefs && temp_prefs->tree, 0);
    g_return_val_if_fail (key, 0);

    value = 0.0f;

    string = g_tree_lookup(temp_prefs->tree, key);

    if (string)
        value = g_ascii_strtod(string, NULL);

    return value;
}
