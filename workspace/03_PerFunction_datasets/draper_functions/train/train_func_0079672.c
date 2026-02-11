process_set_env (Process *process, const gchar *name, const gchar *value)
{
    g_return_if_fail (process != NULL);
    g_return_if_fail (name != NULL);
    g_hash_table_insert (process->priv->env, g_strdup (name), g_strdup (value));
}
