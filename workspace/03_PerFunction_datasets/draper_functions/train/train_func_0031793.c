gtv_unblock_timeout (GtkVideo *gtv)
{
  if (gtv->priv->unblock_timeout)
    g_source_remove (gtv->priv->unblock_timeout);
  gtv->priv->block_next_scale_change = TRUE;
  gtv->priv->unblock_timeout = g_timeout_add (250, unblock_cb, gtv);
}
