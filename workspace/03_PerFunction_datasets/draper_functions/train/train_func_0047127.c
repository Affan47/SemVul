is_conditionally_disabled (GsmApp *app)
{
        GsmAutostartAppPrivate *priv;
        gboolean                res;
        gboolean                disabled;
        char                   *key;
        guint                   kind;

        priv = GSM_AUTOSTART_APP (app)->priv;


        if (priv->condition_string == NULL) {
                return FALSE;
        }

        key = NULL;
        res = parse_condition_string (priv->condition_string, &kind, &key);
        if (! res) {
                g_free (key);
                return TRUE;
        }

        if (key == NULL) {
                return TRUE;
        }

        if (kind == GSM_CONDITION_IF_EXISTS) {
                char *file_path;

                file_path = g_build_filename (g_get_user_config_dir (), key, NULL);
                disabled = !g_file_test (file_path, G_FILE_TEST_EXISTS);
                g_free (file_path);
        } else if (kind == GSM_CONDITION_UNLESS_EXISTS) {
                char *file_path;

                file_path = g_build_filename (g_get_user_config_dir (), key, NULL);
                disabled = g_file_test (file_path, G_FILE_TEST_EXISTS);
                g_free (file_path);
#ifdef HAVE_GCONF
        } else if (kind == GSM_CONDITION_GNOME) {
                GConfClient *client;
                client = gconf_client_get_default ();
                g_assert (GCONF_IS_CLIENT (client));
                disabled = !gconf_client_get_bool (client, key, NULL);
                g_object_unref (client);
#endif
        } else if (kind == GSM_CONDITION_GSETTINGS &&
                   priv->condition_settings != NULL) {
                char **elems;
                elems = g_strsplit (key, " ", 2);
                disabled = !g_settings_get_boolean (priv->condition_settings, elems[1]);
                g_strfreev (elems);
        } else if (kind == GSM_CONDITION_IF_SESSION) {
                GsmManager *manager;
                char *session_name;


                manager = gsm_manager_get ();

                g_object_get (manager, "session-name", &session_name, NULL);
                disabled = strcmp (session_name, key) != 0;
                g_free (session_name);
        } else if (kind == GSM_CONDITION_UNLESS_SESSION) {
                GsmManager *manager;
                char *session_name;


                manager = gsm_manager_get ();

                g_object_get (manager, "session-name", &session_name, NULL);
                disabled = strcmp (session_name, key) == 0;
                g_free (session_name);
        } else {
                disabled = TRUE;
        }


        priv->condition = !disabled;

        g_free (key);

        return disabled;
}
