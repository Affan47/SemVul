grl_registry_lookup_metadata_key_type (GrlRegistry *registry,
                                       GrlKeyID key)
{
  const gchar *key_name;
  GParamSpec *key_pspec;

  g_return_val_if_fail (GRL_IS_REGISTRY (registry), 0);

  key_name = key_id_handler_get_name (&registry->priv->key_id_handler, key);
  if (!key_name) {
    return G_TYPE_INVALID;
  }
  key_pspec = g_hash_table_lookup (registry->priv->system_keys, key_name);

  if (key_pspec) {
    return G_PARAM_SPEC_VALUE_TYPE (key_pspec);
  } else {
    return G_TYPE_INVALID;
  }
}
