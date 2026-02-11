gva_process_has_exited (GvaProcess *process, gint *status)
{
        g_return_val_if_fail (GVA_IS_PROCESS (process), FALSE);

        if (process->priv->exited && status != NULL)
                *status = process->priv->status;

        return process->priv->exited;
}
