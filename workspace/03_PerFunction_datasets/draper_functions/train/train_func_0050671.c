session_lock (Session *session)
{
    g_return_if_fail (session != NULL);
    if (getuid () == 0)
    {
        if (session->priv->login1_session)
            login1_lock_session (session->priv->login1_session);
        else if (session->priv->console_kit_cookie)
            ck_lock_session (session->priv->console_kit_cookie);
    }
}
