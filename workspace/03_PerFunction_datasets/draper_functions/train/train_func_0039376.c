session_set_display_server (Session *session, DisplayServer *display_server)
{
    g_return_if_fail (session != NULL);
    g_return_if_fail (display_server != NULL);
    if (session->priv->display_server)
    {
        display_server_disconnect_session (session->priv->display_server, session);
        g_object_unref (session->priv->display_server);
    }
    session->priv->display_server = g_object_ref (display_server);
}
