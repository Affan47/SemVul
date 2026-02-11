gwy_file_func_run_detect(const gchar *name,
                         const gchar *filename,
                         gboolean only_name)
{
    GwyFileFuncInfo *func_info;
    GwyFileDetectInfo fileinfo;
    gint score = 0;

    g_return_val_if_fail(filename, 0);
    func_info = g_hash_table_lookup(file_funcs, name);
    g_return_val_if_fail(func_info, 0);
    if (!func_info->detect)
        return 0;

    fileinfo.name = filename;

    if (gwy_file_detect_fill_info(&fileinfo, only_name)) {
        score = func_info->detect(&fileinfo, only_name, name);
        gwy_file_detect_free_info(&fileinfo);
    }

    return score;
}
