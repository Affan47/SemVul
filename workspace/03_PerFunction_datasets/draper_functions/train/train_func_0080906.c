evd_web_transport_server_accept_peer (EvdTransport *transport, EvdPeer *peer)
{
  EvdPeerManager *peer_manager;
  HandshakeData *data;

  peer_manager = evd_transport_get_peer_manager (transport);

  if (evd_peer_manager_lookup_peer (peer_manager,
                                    evd_peer_get_id (peer)) == NULL)
    {
      evd_peer_manager_add_peer (peer_manager, peer);

      EVD_TRANSPORT_GET_INTERFACE (transport)->
        notify_new_peer (transport, peer);
    }

  data = g_object_get_data (G_OBJECT (peer), HANDSHAKE_DATA_KEY);
  if (data == NULL)
    return TRUE;

  g_signal_handlers_disconnect_by_func (data->conn,
                                        evd_web_transport_server_conn_on_close,
                                        peer);

  evd_web_transport_server_respond_handshake (data, peer);

  g_object_set_data (G_OBJECT (peer), HANDSHAKE_DATA_KEY, NULL);
  g_object_unref (peer);

  return TRUE;
}
