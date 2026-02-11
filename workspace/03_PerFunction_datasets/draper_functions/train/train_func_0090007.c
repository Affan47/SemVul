spawn_slave (GdmSlaveProxy *slave)
{
        gboolean    result;
        GError     *error;

        g_debug ("GdmSlaveProxy: Running command: %s", slave->priv->command);

        error = NULL;
        result = spawn_command_line_async (slave->priv->command,
                                           slave->priv->log_path,
                                           NULL,
                                           &slave->priv->pid,
                                           &error);
        if (! result) {
                g_warning ("Could not start command '%s': %s", slave->priv->command, error->message);
                g_error_free (error);
                goto out;
        }

        g_debug ("GdmSlaveProxy: Started slave with pid %d", slave->priv->pid);

        slave->priv->child_watch_id = g_child_watch_add_full (G_PRIORITY_DEFAULT,
                                                              slave->priv->pid,
                                                              (GChildWatchFunc)child_watch,
                                                              g_object_ref (slave),
                                                              (GDestroyNotify)
                                                              clear_child_watch);

        result = TRUE;

 out:

        return result;
}
