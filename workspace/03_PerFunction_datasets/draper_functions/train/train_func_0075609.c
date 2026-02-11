get_session_keyfile (const char *session,
                     char      **actual_session,
                     gboolean   *is_fallback)
{
        GKeyFile *keyfile;
        gboolean  session_runnable;
        char     *value;
        GError *error = NULL;

        *actual_session = NULL;

        g_debug ("fill: *** Getting session '%s'", session);

        keyfile = find_valid_session_keyfile (session);

        if (!keyfile)
                return NULL;

        session_runnable = TRUE;

        value = g_key_file_get_string (keyfile,
                                       GSM_KEYFILE_SESSION_GROUP, GSM_KEYFILE_RUNNABLE_KEY,
                                       NULL);
        if (!IS_STRING_EMPTY (value)) {
                g_debug ("fill: *** Launching helper '%s' to know if session is runnable", value);
                session_runnable = gsm_process_helper (value, GSM_RUNNABLE_HELPER_TIMEOUT, &error);
                if (!session_runnable) {
                        g_warning ("Session '%s' runnable check failed: %s", session,
                                   error->message);
                        g_clear_error (&error);
                }
        }
        g_free (value);

        if (session_runnable) {
                session_runnable = check_required (keyfile);
        }

        if (session_runnable) {
                *actual_session = g_strdup (session);
                if (is_fallback)
                        *is_fallback = FALSE;
                return keyfile;
        }

        g_debug ("fill: *** Session is not runnable");


        value = g_key_file_get_string (keyfile,
                                       GSM_KEYFILE_SESSION_GROUP, GSM_KEYFILE_FALLBACK_KEY,
                                       NULL);

        g_key_file_free (keyfile);
        keyfile = NULL;

        if (!IS_STRING_EMPTY (value)) {
                if (is_fallback)
                        *is_fallback = TRUE;
                keyfile = get_session_keyfile (value, actual_session, NULL);
        }
        g_free (value);

        return keyfile;
}
