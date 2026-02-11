gdm_session_settings_set_session_name (GdmSessionSettings *settings,
                                       const char         *session_name)
{
        g_return_if_fail (GDM_IS_SESSION_SETTINGS (settings));

        if (settings->priv->session_name == NULL ||
            strcmp (settings->priv->session_name, session_name) != 0) {
                settings->priv->session_name = g_strdup (session_name);
                g_object_notify (G_OBJECT (settings), "session-name");
        }
}
