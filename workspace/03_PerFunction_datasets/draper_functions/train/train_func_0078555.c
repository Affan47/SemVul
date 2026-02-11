on_format(GtkAction* act, gpointer user_data)
{
    FmPlacesItem* item = (FmPlacesItem*)user_data;
    char *unix_path;

    if (fm_config->format_cmd == NULL || fm_config->format_cmd[0] == 0)
        return;
    unix_path = g_volume_get_identifier(fm_places_item_get_volume(item),
                                        G_VOLUME_IDENTIFIER_KIND_UNIX_DEVICE);
    if (unix_path)
    {

        g_debug("formatting %s ...", unix_path);
        FmPath *path = fm_path_new_for_path(unix_path);
        g_free(unix_path);
        FmPathList *paths = fm_path_list_new();
        fm_path_list_push_tail(paths, path);
        fm_path_unref(path);
        fm_launch_command_simple(_get_gtk_window_from_action(act), NULL, 0,
                                 fm_config->format_cmd, paths);
        fm_path_list_unref(paths);
    }
}
