ck_seat_remove_session (CkSeat         *seat,
                        CkSession      *session,
                        GError        **error)
{
        char       *ssid;
        char      *orig_ssid;
        CkSession *orig_session;
        gboolean   res;
        gboolean   ret;

        g_return_val_if_fail (CK_IS_SEAT (seat), FALSE);

        ret = FALSE;
        ssid = NULL;
        ck_session_get_id (session, &ssid, NULL);


        res = g_hash_table_lookup_extended (seat->priv->sessions,
                                            ssid,
                                            (gpointer *)&orig_ssid,
                                            (gpointer *)&orig_session);
        if (! res) {
                g_debug ("Session %s is not attached to seat %s", ssid, seat->priv->id);
                g_set_error (error,
                             CK_SEAT_ERROR,
                             CK_SEAT_ERROR_GENERAL,
                             _("Session is not attached to this seat"));
                goto out;
        }

        g_signal_handlers_disconnect_by_func (session, session_activate, seat);


        g_hash_table_steal (seat->priv->sessions, ssid);

        g_debug ("Emitting session-removed: %s", ssid);


        g_signal_emit (seat, signals [SESSION_REMOVED_FULL], 0, session);
        g_signal_emit (seat, signals [SESSION_REMOVED], 0, ssid);


        maybe_update_active_session (seat);

        if (orig_session != NULL) {
                g_object_unref (orig_session);
        }
        g_free (orig_ssid);

        ret = TRUE;
 out:
        g_free (ssid);

        return ret;
}
