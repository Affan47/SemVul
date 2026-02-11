handle_login (Greeter *greeter, guint32 sequence_number, const gchar *username)
{
    const gchar *autologin_username, *service;
    gboolean is_interactive;

    if (username[0] == '\0')
    {
        l_debug (greeter, "Greeter start authentication");
        username = NULL;
    }
    else
        l_debug (greeter, "Greeter start authentication for %s", username);

    reset_session (greeter);

    if (greeter->priv->active_username)
        g_free (greeter->priv->active_username);
    greeter->priv->active_username = g_strdup (username);
    g_object_notify (G_OBJECT (greeter), "active-username");

    greeter->priv->authentication_sequence_number = sequence_number;
    g_signal_emit (greeter, signals[CREATE_SESSION], 0, &greeter->priv->authentication_session);
    if (!greeter->priv->authentication_session)
    {
        send_end_authentication (greeter, sequence_number, "", PAM_USER_UNKNOWN);
        return;
    }

    g_signal_connect (G_OBJECT (greeter->priv->authentication_session), "got-messages", G_CALLBACK (pam_messages_cb), greeter);
    g_signal_connect (G_OBJECT (greeter->priv->authentication_session), "authentication-complete", G_CALLBACK (authentication_complete_cb), greeter);


    autologin_username = g_hash_table_lookup (greeter->priv->hints, "autologin-user");
    if (autologin_username != NULL && g_strcmp0 (username, autologin_username) == 0)
    {
        service = greeter->priv->autologin_pam_service;
        is_interactive = FALSE;
    }
    else
    {
        service = greeter->priv->pam_service;
        is_interactive = TRUE;
    }


    session_set_pam_service (greeter->priv->authentication_session, service);
    session_set_username (greeter->priv->authentication_session, username);
    session_set_do_authenticate (greeter->priv->authentication_session, TRUE);
    session_set_is_interactive (greeter->priv->authentication_session, is_interactive);
    session_start (greeter->priv->authentication_session);
}
