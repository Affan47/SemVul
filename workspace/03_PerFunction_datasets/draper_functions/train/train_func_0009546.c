cut_utils_build_path_va_list (const gchar *path, va_list args)
{
    GArray *elements;
    gchar *element, *concatenated_path;

    if (!path)
        return NULL;

    elements = g_array_new(TRUE, FALSE, sizeof(char *));

    g_array_append_val(elements, path);
    while ((element = va_arg(args, gchar *))) {
        g_array_append_val(elements, element);
    }
    concatenated_path =
        cut_utils_build_path_array((const gchar **)(elements->data));
    g_array_free(elements, TRUE);

    return concatenated_path;
}
