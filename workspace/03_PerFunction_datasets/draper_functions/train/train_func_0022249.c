gdm_settings_desktop_backend_set_value (GdmSettingsBackend *backend,
                                        const char         *key,
                                        const char         *value,
                                        GError            **error)
{
        GError *local_error;
        char   *old_val;
        char   *g;
        char   *k;
        char   *l;

        g_return_val_if_fail (GDM_IS_SETTINGS_BACKEND (backend), FALSE);
        g_return_val_if_fail (key != NULL, FALSE);


        if (! parse_key_string (key, &g, &k, &l, NULL)) {
                g_set_error (error, GDM_SETTINGS_BACKEND_ERROR, GDM_SETTINGS_BACKEND_ERROR_KEY_NOT_FOUND, "Key not found");
                return FALSE;
        }

        local_error = NULL;
        old_val = g_key_file_get_value (GDM_SETTINGS_DESKTOP_BACKEND (backend)->priv->key_file,
                                        g,
                                        k,
                                        &local_error);
        if (local_error != NULL) {
                g_error_free (local_error);
        }


        local_error = NULL;
        g_key_file_set_value (GDM_SETTINGS_DESKTOP_BACKEND (backend)->priv->key_file,
                              g,
                              k,
                              value);

        GDM_SETTINGS_DESKTOP_BACKEND (backend)->priv->dirty = TRUE;
        queue_save (GDM_SETTINGS_DESKTOP_BACKEND (backend));

        gdm_settings_backend_value_changed (backend, key, old_val, value);

        g_free (old_val);

        return TRUE;
}
