grl_related_keys_remove (GrlRelatedKeys *relkeys,
                         GrlKeyID key)
{
  g_return_if_fail (GRL_IS_RELATED_KEYS (relkeys));
  g_return_if_fail (key != GRL_METADATA_KEY_INVALID);

  g_hash_table_remove (relkeys->priv->data, GRLKEYID_TO_POINTER (key));
}
