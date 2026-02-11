gdm_chooser_session_start (GdmChooserSession *session,
                           GError           **error)
{
        g_return_val_if_fail (GDM_IS_CHOOSER_SESSION (session), FALSE);

        session->priv->remote_greeter = gdm_client_get_remote_greeter_sync (session->priv->client,
                                                                            NULL,
                                                                            error);
        if (session->priv->remote_greeter == NULL) {
                return FALSE;
        }

        session->priv->chooser = gdm_client_get_chooser_sync (session->priv->client,
                                                              NULL,
                                                              error);
        if (session->priv->chooser == NULL) {
                return FALSE;
        }

        start_settings_daemon (session);
        start_window_manager (session);


        session->priv->chooser_dialog = gdm_host_chooser_dialog_new (GDM_CHOOSER_HOST_KIND_XDMCP);
        g_signal_connect (session->priv->chooser_dialog,
                          "response",
                          G_CALLBACK (on_dialog_response),
                          session);
        gtk_widget_show (session->priv->chooser_dialog);

        return TRUE;
}
