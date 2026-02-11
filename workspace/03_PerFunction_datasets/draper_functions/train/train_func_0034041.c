evd_transport_reject_peer (EvdTransport *self, EvdPeer *peer)
{
  EvdTransportInterface *iface;

  g_return_val_if_fail (EVD_IS_TRANSPORT (self), FALSE);
  g_return_val_if_fail (EVD_IS_PEER (peer), FALSE);

  iface = EVD_TRANSPORT_GET_INTERFACE (self);
  if (iface->reject_peer != NULL)
    {
      return iface->reject_peer (self, peer);
    }
  else
    {
      g_object_unref (peer);
      return TRUE;
    }
}
