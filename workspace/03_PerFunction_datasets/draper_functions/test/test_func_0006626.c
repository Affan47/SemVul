process_finalize (GObject *object)
{
        GvaProcess *process = GVA_PROCESS (object);

        gva_error_handle (&process->error);

        if (process->priv->stdin_channel != NULL)
                g_io_channel_unref (process->priv->stdin_channel);
        if (process->priv->stdout_channel != NULL)
                g_io_channel_unref (process->priv->stdout_channel);
        if (process->priv->stderr_channel != NULL)
                g_io_channel_unref (process->priv->stderr_channel);

        while (!g_queue_is_empty (process->priv->stdout_lines))
                g_free (g_queue_pop_head (process->priv->stdout_lines));

        while (!g_queue_is_empty (process->priv->stderr_lines))
                g_free (g_queue_pop_head (process->priv->stderr_lines));

        g_queue_free (process->priv->stdout_lines);
        g_queue_free (process->priv->stderr_lines);


        G_OBJECT_CLASS (gva_process_parent_class)->finalize (object);
}
