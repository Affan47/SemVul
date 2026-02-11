_check_native_display_names(FmPath *path)
{
    char *path_str, *disp_name;

    if (path == NULL || _fm_path_get_display_name(path) != NULL)
        return;
    path_str = fm_path_to_str(path);
    disp_name = g_filename_display_basename(path_str);
    g_free(path_str);
    _fm_path_set_display_name(path, disp_name);
    g_free(disp_name);
    _check_native_display_names(fm_path_get_parent(path));
}
