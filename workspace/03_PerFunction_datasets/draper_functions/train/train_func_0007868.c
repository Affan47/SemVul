_gsp_app_manager_handle_delete (GspAppManager *manager,
                                GspApp        *app,
                                const char    *basename,
                                int            index)
{
        unsigned int position;
        unsigned int system_position;

        position = gsp_app_get_xdg_position (app);
        system_position = gsp_app_get_xdg_system_position (app);

        if (system_position < index) {

                return;
        }

        if (index < position) {


                 g_assert (index == 0);
                 return;
        }

        if (position == index &&
            (system_position == index || system_position == G_MAXUINT)) {


                _gsp_app_manager_app_removed (manager, app);
                return;
        }

        if (system_position == index) {


                int new_system;

                new_system = _gsp_app_manager_find_dir_with_basename (manager,
                                                                      basename,
                                                                      index);
                if (new_system < 0) {
                        gsp_app_set_xdg_system_position (app, G_MAXUINT);
                } else {
                        gsp_app_set_xdg_system_position (app, new_system);
                }

                return;
        }

        if (position == index) {


                const char *dir;

                dir = gsp_app_manager_get_dir (manager, system_position);
                if (dir) {
                        char *path;

                        path = g_build_filename (dir, basename, NULL);
                        gsp_app_reload_at (app, path,
                                           (unsigned int) system_position);
                        g_free (path);
                } else {
                        _gsp_app_manager_app_removed (manager, app);
                }

                return;
        }

        g_assert_not_reached ();
}
