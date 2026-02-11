grl_operation_options_finalize (GrlOperationOptions *self)
{
  g_hash_table_unref (self->priv->data);
  g_hash_table_unref (self->priv->key_filter);
  g_hash_table_unref (self->priv->key_range_filter);
  g_clear_object (&self->priv->caps);
  G_OBJECT_CLASS (grl_operation_options_parent_class)->finalize ((GObject *) self);
}
