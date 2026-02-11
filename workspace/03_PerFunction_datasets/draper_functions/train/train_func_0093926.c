common_user_list_finalize (GObject *object)
{
    CommonUserList *self = COMMON_USER_LIST (object);
    CommonUserListPrivate *priv = GET_LIST_PRIVATE (self);


    g_list_free_full (priv->users, g_object_unref);
    g_list_free_full (priv->sessions, g_object_unref);

    if (priv->user_added_signal)
        g_dbus_connection_signal_unsubscribe (priv->bus, priv->user_added_signal);
    if (priv->user_removed_signal)
        g_dbus_connection_signal_unsubscribe (priv->bus, priv->user_removed_signal);
    if (priv->session_added_signal)
        g_dbus_connection_signal_unsubscribe (priv->bus, priv->session_added_signal);
    if (priv->session_removed_signal)
        g_dbus_connection_signal_unsubscribe (priv->bus, priv->session_removed_signal);
    g_object_unref (priv->bus);
    if (priv->passwd_monitor)
        g_object_unref (priv->passwd_monitor);

    G_OBJECT_CLASS (common_user_list_parent_class)->finalize (object);
}
