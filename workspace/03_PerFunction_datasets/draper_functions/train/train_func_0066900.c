tp_call_stream_endpoint_add_new_candidate (TpCallStreamEndpoint *self,
    TpStreamComponent component,
    const gchar *address,
    guint port,
    const GHashTable *info_hash)
{
  GPtrArray *candidates;
  GValueArray *c;

  g_return_if_fail (TP_IS_CALL_STREAM_ENDPOINT (self));
  g_return_if_fail (address != NULL);
  g_return_if_fail (port < 65536);
  g_return_if_fail (info_hash != NULL);

  DEBUG ("Add one candidates to endpoint %s", self->priv->object_path);

  c = tp_value_array_build (4,
      G_TYPE_UINT, component,
      G_TYPE_STRING, address,
      G_TYPE_UINT, port,
      TP_HASH_TYPE_CANDIDATE_INFO, info_hash,
      G_TYPE_INVALID);

  g_ptr_array_add (self->priv->remote_candidates, c);

  candidates = g_ptr_array_new ();
  g_ptr_array_add (candidates, c);
  tp_svc_call_stream_endpoint_emit_remote_candidates_added (self,
      candidates);
  g_ptr_array_unref (candidates);
}
