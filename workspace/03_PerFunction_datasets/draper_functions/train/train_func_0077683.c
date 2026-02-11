add_handle_owners_helper (gpointer key,
                          gpointer value,
                          gpointer user_data)
{
  TpHandle local_handle = GPOINTER_TO_UINT (key);
  TpGroupMixin *mixin = user_data;

  g_return_if_fail (local_handle != 0);

  g_hash_table_insert (mixin->priv->handle_owners, key, value);
}
