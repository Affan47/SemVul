gdm_session_bypasses_xsession (GdmSession *self)
{
        GError     *error;
        GKeyFile   *key_file;
        gboolean    res;
        gboolean    bypasses_xsession = FALSE;
        char       *filename;

        g_return_val_if_fail (self != NULL, FALSE);
        g_return_val_if_fail (GDM_IS_SESSION (self), FALSE);

        filename = g_strdup_printf ("%s.desktop", get_session_name (self));

        key_file = g_key_file_new ();
        error = NULL;
        res = g_key_file_load_from_dirs (key_file,
                                         filename,
                                         get_system_session_dirs (),
                                         NULL,
                                         G_KEY_FILE_NONE,
                                         &error);
        if (! res) {
                g_debug ("GdmSession: File '%s' not found: %s", filename, error->message);
                goto out;
        }

        error = NULL;
        res = g_key_file_has_key (key_file, G_KEY_FILE_DESKTOP_GROUP, "X-GDM-BypassXsession", NULL);
        if (!res) {
                goto out;
        } else {
                bypasses_xsession = g_key_file_get_boolean (key_file, G_KEY_FILE_DESKTOP_GROUP, "X-GDM-BypassXsession", &error);
                if (error) {
                        bypasses_xsession = FALSE;
                        g_error_free (error);
                        goto out;
                }
                if (bypasses_xsession) {
                        g_debug ("GdmSession: Session %s bypasses Xsession wrapper script", filename);
                }
        }

out:
        g_free (filename);
        return bypasses_xsession;
}
