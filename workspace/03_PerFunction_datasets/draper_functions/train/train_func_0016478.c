process_key_value(const char *key, char *value, int force) {
    char *key_lower = fs_ascii_strdown(key, -1);
    fs_strdelimit (key_lower, "-", '_');


    if (!force && fs_config_get_const_string(key_lower)) {
        fs_log("%s = %s (ignored)\n", key_lower, value);
        free(key_lower);
        free(value);
    }
    else {
        fs_strstrip(value);
        fs_log("%s = %s\n", key_lower, value);

        fs_hash_table_insert(g_hash_table, key_lower, value);
    }
}
