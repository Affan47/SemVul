_fm_path_display_name(FmPath* path, gboolean *is_query)
{
    char* disp;

    if(G_LIKELY(path->parent))
    {
        char* disp_parent;
        char* disp_base;
        if (G_UNLIKELY(*is_query))
            goto _is_query;
        else if (fm_path_is_native(path))
        {
            disp_parent = _fm_path_display_name(path->parent, is_query);
            disp_base = fm_path_display_basename(path);
        }
        else if (strchr(path->name, '?') == NULL)
        {

            disp_parent = _fm_path_display_name(path->parent, is_query);
            if (G_UNLIKELY(*is_query))
                goto _is_query2;
            else
                disp_base = fm_path_display_basename(path);
        }
        else
        {

            *is_query = TRUE;
_is_query:
            disp_parent = _fm_path_display_name(path->parent, is_query);
_is_query2:
            disp = g_strjoin(NULL, disp_parent, path->name, NULL);
            g_free(disp_parent);
            return disp;
        }
        if (fm_path_is_native(path))
            disp = g_build_filename( disp_parent, disp_base, NULL);
        else
            disp = g_build_path("/", disp_parent, disp_base, NULL);
        g_free(disp_parent);
        g_free(disp_base);
    }
    else
        disp = g_uri_unescape_string(path->name, NULL);
    return disp;
}
