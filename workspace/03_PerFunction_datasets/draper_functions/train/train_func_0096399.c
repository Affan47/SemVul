session_finalize (GObject *object)
{
    Session *self = SESSION (object);
    int i;

    if (self->priv->config)
        g_object_unref (self->priv->config);
    if (self->priv->display_server)
        g_object_unref (self->priv->display_server);
    if (self->priv->pid)
        kill (self->priv->pid, SIGKILL);
    close (self->priv->to_child_input);
    close (self->priv->from_child_output);
    if (self->priv->from_child_channel)
        g_io_channel_unref (self->priv->from_child_channel);
    if (self->priv->from_child_watch)
        g_source_remove (self->priv->from_child_watch);
    if (self->priv->child_watch)
        g_source_remove (self->priv->child_watch);
    g_free (self->priv->username);
    if (self->priv->user)
        g_object_unref (self->priv->user);
    g_free (self->priv->pam_service);
    for (i = 0; i < self->priv->messages_length; i++)
        g_free ((char *) self->priv->messages[i].msg);
    g_free (self->priv->messages);
    g_free (self->priv->authentication_result_string);
    g_free (self->priv->log_filename);
    g_free (self->priv->tty);
    g_free (self->priv->xdisplay);
    if (self->priv->x_authority)
        g_object_unref (self->priv->x_authority);
    g_free (self->priv->remote_host_name);
    g_free (self->priv->login1_session);
    g_free (self->priv->console_kit_cookie);
    g_list_free_full (self->priv->env, g_free);
    g_strfreev (self->priv->argv);

    G_OBJECT_CLASS (session_parent_class)->finalize (object);
}
