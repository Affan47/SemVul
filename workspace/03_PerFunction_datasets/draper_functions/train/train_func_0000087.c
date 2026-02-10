worker_on_saved_session_name_read (GdmDBusWorker          *worker,
                                   const char             *session_name,
                                   GdmSessionConversation *conversation)
{
        GdmSession *self = conversation->session;

        if (! get_session_command_for_name (session_name, NULL)) {

                g_debug ("GdmSession: not using invalid .dmrc session: %s", session_name);
                g_free (self->priv->saved_session);
                self->priv->saved_session = NULL;
                return;
        }

        if (strcmp (session_name,
                    get_default_session_name (self)) != 0) {
                g_free (self->priv->saved_session);
                self->priv->saved_session = g_strdup (session_name);

                if (self->priv->greeter_interface != NULL) {
                        gdm_dbus_greeter_emit_default_session_name_changed (self->priv->greeter_interface,
                                                                            session_name);
                }
        }
}
