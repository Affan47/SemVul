filetea_node_finalize (GObject *obj)
{
  FileteaNode *self = FILETEA_NODE (obj);

  g_free (self->priv->id);

  g_object_unref (self->priv->rpc);
  g_object_unref (self->priv->transport);
  g_object_unref (self->priv->webdir);
  g_object_unref (self->priv->jquery_webdir);
  g_object_unref (self->priv->selector);

  if (self->priv->log_queue != NULL)
    {
      while (g_queue_get_length (self->priv->log_queue) > 0)
        {
          gchar *entry;
          entry = g_queue_pop_head (self->priv->log_queue);
          g_free (entry);
        }
      g_queue_free (self->priv->log_queue);
    }

  if (self->priv->log_output_stream != NULL)
    g_object_unref (self->priv->log_output_stream);

  if (self->priv->log_filename != NULL)
    g_free (self->priv->log_filename);

  G_OBJECT_CLASS (filetea_node_parent_class)->finalize (obj);
}
