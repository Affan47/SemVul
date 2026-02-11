unity_system_compositor_connect_session (DisplayServer *display_server, Session *session)
{
    UnitySystemCompositor *compositor = UNITY_SYSTEM_COMPOSITOR (display_server);
    const gchar *name;

    if (compositor->priv->socket)
        session_set_env (session, "MIR_SOCKET", compositor->priv->socket);
    if (IS_GREETER (session))
        name = "greeter-0";
    else
        name = "session-0";
    session_set_env (session, "MIR_SERVER_NAME", name);

    if (compositor->priv->vt >= 0)
    {
        gchar *value = g_strdup_printf ("%d", compositor->priv->vt);
        session_set_env (session, "XDG_VTNR", value);
        g_free (value);
    }
}
