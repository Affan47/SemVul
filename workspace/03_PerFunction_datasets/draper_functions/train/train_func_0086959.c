dispose (GObject *object)
{
    GCutEggPrivate *priv;

    priv = GCUT_EGG_GET_PRIVATE(object);
    if (priv->command) {
        g_strfreev(priv->command);
        priv->command = NULL;
    }

    if (priv->process_watch_id && priv->pid) {
        gcut_egg_kill(GCUT_EGG(object), SIGTERM);
        if (priv->forced_termination_wait_time > 0) {
            gboolean is_timeout = FALSE;
            guint timeout_wait_id;

            timeout_wait_id = g_timeout_add(priv->forced_termination_wait_time,
                                            cb_timeout_wait,
                                            &is_timeout);
            while (!is_timeout && priv->process_watch_id > 0 && priv->pid > 0)
                g_main_context_iteration(NULL, TRUE);
            g_source_remove(timeout_wait_id);
        }
    }

    if (priv->process_watch_id)
        remove_child_watch_func(priv);

    if (priv->pid) {
        gcut_egg_close(GCUT_EGG(object));
    }

    dispose_io_channel(priv);

    G_OBJECT_CLASS(gcut_egg_parent_class)->dispose(object);
}
