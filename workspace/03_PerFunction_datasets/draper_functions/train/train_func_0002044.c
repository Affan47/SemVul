remove_jid_suffix (TpawAccountWidget *self,
    const gchar *str)
{
  g_assert (self->priv->jid_suffix != NULL);

  if (!g_str_has_suffix (str, self->priv->jid_suffix))
    return g_strdup (str);

  return g_strndup (str, strlen (str) - strlen (self->priv->jid_suffix));
}
