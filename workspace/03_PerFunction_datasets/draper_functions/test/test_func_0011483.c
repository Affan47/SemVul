temp_prefs_flush(TempPrefs *temp_prefs) {
    g_return_if_fail (temp_prefs);
    g_return_if_fail (temp_prefs->tree);

    lock_prefs_table();

    g_tree_foreach(temp_prefs->tree, flush_key, NULL);

    unlock_prefs_table();
}
