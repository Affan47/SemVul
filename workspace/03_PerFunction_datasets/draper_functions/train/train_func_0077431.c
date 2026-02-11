tp_group_mixin_finalize (GObject *obj)
{
  TpGroupMixin *mixin = TP_GROUP_MIXIN (obj);

  tp_handle_set_destroy (mixin->priv->actors);

  g_hash_table_unref (mixin->priv->handle_owners);
  g_hash_table_unref (mixin->priv->local_pending_info);

  if (mixin->priv->externals)
    g_ptr_array_unref (mixin->priv->externals);

  g_slice_free (TpGroupMixinPrivate, mixin->priv);

  tp_handle_set_destroy (mixin->members);
  tp_handle_set_destroy (mixin->local_pending);
  tp_handle_set_destroy (mixin->remote_pending);
}
