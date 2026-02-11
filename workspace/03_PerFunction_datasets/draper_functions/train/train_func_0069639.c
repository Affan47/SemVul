greeter_finalize (GObject *object)
{
    Greeter *self;

    self = GREETER (object);

    g_free (self->priv->pam_service);
    g_free (self->priv->autologin_pam_service);
    secure_free (self, self->priv->read_buffer);
    g_hash_table_unref (self->priv->hints);
    g_free (self->priv->remote_session);
    g_free (self->priv->active_username);
    if (self->priv->authentication_session)
    {
        g_signal_handlers_disconnect_matched (self->priv->authentication_session, G_SIGNAL_MATCH_DATA, 0, 0, NULL, NULL, self);
        g_object_unref (self->priv->authentication_session);
    }
    if (self->priv->to_greeter_channel)
        g_io_channel_unref (self->priv->to_greeter_channel);
    if (self->priv->from_greeter_channel)
        g_io_channel_unref (self->priv->from_greeter_channel);
    if (self->priv->from_greeter_watch)
        g_source_remove (self->priv->from_greeter_watch);

    G_OBJECT_CLASS (greeter_parent_class)->finalize (object);
}
