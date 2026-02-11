on_ready_to_request_timed_login (GdmSession         *session,
                                 GSimpleAsyncResult *result,
                                 gpointer           *user_data)
{
        int delay = GPOINTER_TO_INT (user_data);
        GCancellable *cancellable;
        char         *username;

        cancellable = g_object_get_data (G_OBJECT (result),
                                         "cancellable");
        if (g_cancellable_is_cancelled (cancellable)) {
                return;
        }

        username = g_simple_async_result_get_source_tag (result);

        gdm_session_request_timed_login (session, username, delay);

        g_object_weak_unref (G_OBJECT (session),
                             (GWeakNotify)
                             g_cancellable_cancel,
                             cancellable);
        g_object_weak_unref (G_OBJECT (session),
                             (GWeakNotify)
                             g_object_unref,
                             cancellable);
        g_object_weak_unref (G_OBJECT (session),
                             (GWeakNotify)
                             g_free,
                             username);

        g_free (username);
}
