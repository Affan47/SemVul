cmp_filepath (gconstpointer a, gconstpointer b)
{
    const gchar *file1 = a;
    const gchar *file2 = b;
    gboolean file1_content;
    gboolean file2_content;

    file1_content = (file1 && *file1);
    file2_content = (file2 && *file2);

    if (file1_content && !file2_content) {
        return 1;
    }
    if (!file1_content && file2_content) {
        return -1;
    }

    if (g_str_has_prefix (file1, INPUT_PAD_PAD_SYSTEM_DIR) &&
        !g_str_has_prefix (file2, INPUT_PAD_PAD_SYSTEM_DIR)) {
        return -1;
    }
    if (!g_str_has_prefix (file1, INPUT_PAD_PAD_SYSTEM_DIR) &&
        g_str_has_prefix (file2, INPUT_PAD_PAD_SYSTEM_DIR)) {
        return 1;
    }
    return g_strcmp0 (file1, file2);
}
