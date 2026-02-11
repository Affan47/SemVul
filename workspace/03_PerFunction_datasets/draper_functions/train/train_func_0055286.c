lock_initialization (int     *argc,
                     char   **argv,
                     char   **nolock_reason,
                     gboolean verbose)
{
        if (nolock_reason != NULL) {
                *nolock_reason = NULL;
        }

#ifdef NO_LOCKING
        if (nolock_reason != NULL) {
                *nolock_reason = g_strdup ("not compiled with locking support");
        }

        return FALSE;
#else


        if (! gs_auth_init ()) {
                if (nolock_reason != NULL) {
                        *nolock_reason = g_strdup ("error getting password");
                }

                return FALSE;
        }


        if (getenv ("RUNNING_UNDER_GDM")) {
                if (nolock_reason != NULL) {
                        *nolock_reason = g_strdup ("running under GDM");
                }

                return FALSE;
        }


        {
                gboolean macos = FALSE;

#ifdef __APPLE__


                macos = TRUE;
#endif

                if (macos) {
                        if (nolock_reason != NULL) {
                                *nolock_reason = g_strdup ("Cannot lock securely on MacOS X");
                        }

                        return FALSE;
                }
        }

#endif

        return TRUE;
}
