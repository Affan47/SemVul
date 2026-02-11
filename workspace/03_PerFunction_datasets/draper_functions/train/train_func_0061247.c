gwy_file_func_run_save(const gchar *name,
                       GwyContainer *data,
                       const gchar *filename,
                       GwyRunType mode,
                       GError **error)
{
    GwyFileFuncInfo *func_info;
    gboolean status;

    g_return_val_if_fail(!error || !*error, FALSE);
    g_return_val_if_fail(filename, FALSE);
    g_return_val_if_fail(GWY_IS_CONTAINER(data), FALSE);
    func_info = g_hash_table_lookup(file_funcs, name);
    g_return_val_if_fail(func_info, FALSE);
    g_return_val_if_fail(func_info->save, FALSE);

    g_object_ref(data);
    status = func_info->save(data, filename, mode, error, name);
    if (status)
        gwy_file_type_info_set(data, name, filename);
    g_object_unref(data);

    return status;
}
