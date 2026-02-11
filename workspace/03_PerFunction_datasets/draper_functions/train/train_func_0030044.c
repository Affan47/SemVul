panel_layout_delete_toplevel (const char *toplevel_id)
{
        char  *path;
        char  *id_copy;
        char **objects;
        int    i;

        if (PANEL_GLIB_STR_EMPTY (toplevel_id))
                return;


        id_copy = g_strdup (toplevel_id);

        if (!panel_gsettings_remove_all_from_strv (layout_settings,
                                                   PANEL_LAYOUT_TOPLEVEL_ID_LIST_KEY,
                                                   id_copy)) {
                g_free (id_copy);
                return;
        }

        path = g_strdup_printf ("%s%s/",
                                PANEL_LAYOUT_TOPLEVEL_PATH, id_copy);
        panel_dconf_recursive_reset (path, NULL);


        objects = g_settings_get_strv (layout_settings,
                                       PANEL_LAYOUT_OBJECT_ID_LIST_KEY);

        for (i = 0; objects[i] != NULL; i++) {
                GSettings *settings;
                char       *object_toplevel_id;

                path = g_strdup_printf ("%s%s/",
                                        PANEL_LAYOUT_OBJECT_PATH, objects[i]);

                settings = g_settings_new_with_path (PANEL_OBJECT_SCHEMA, path);
                object_toplevel_id = g_settings_get_string (settings,
                                                            PANEL_OBJECT_TOPLEVEL_ID_KEY);

                g_object_unref (settings);
                g_free (path);

                if (g_strcmp0 (id_copy, object_toplevel_id) == 0)
                        panel_layout_delete_object (objects[i]);

                g_free (object_toplevel_id);
        }

        g_strfreev (objects);

        g_free (id_copy);
}
