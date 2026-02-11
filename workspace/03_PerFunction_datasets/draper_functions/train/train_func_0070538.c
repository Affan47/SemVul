evd_peer_manager_get_all_peers (EvdPeerManager *self)
{
  g_return_val_if_fail (EVD_IS_PEER_MANAGER (self), NULL);

  evd_peer_manager_cleanup_peers (self);

  return g_hash_table_get_values (self->priv->peers);
}
