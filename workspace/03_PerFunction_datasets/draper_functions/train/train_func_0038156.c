evd_transport_close_peer (EvdTransport  *self,
                          EvdPeer       *peer,
                          gboolean       gracefully,
                          GError       **error)
{
  EvdTransportInterface *iface;
  EvdPeerManager *peer_manager;
  gpointer bag;

  g_return_if_fail (EVD_IS_TRANSPORT (self));
  g_return_if_fail (EVD_IS_PEER (peer));

  bag = g_object_get_data (G_OBJECT (peer), PEER_CLOSING_KEY);
  if (bag != NULL)
    return;

  g_object_ref (self);
  g_object_set_data (G_OBJECT (peer), PEER_CLOSING_KEY, self);

  g_object_ref (peer);

  peer_manager = EVD_TRANSPORT_GET_INTERFACE (self)->peer_manager;
  evd_peer_manager_close_peer (peer_manager, peer, gracefully);

  evd_peer_close (peer, gracefully);

  iface = EVD_TRANSPORT_GET_INTERFACE (self);

  if (iface->peer_closed != NULL)
    iface->peer_closed (self, peer, gracefully);

  evd_transport_notify_peer_closed (self, peer, gracefully);

  g_object_set_data (G_OBJECT (peer), PEER_CLOSING_KEY, NULL);
  g_object_unref (self);

  g_object_unref (peer);
}
