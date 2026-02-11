enet_protocol_notify_connect (ENetHost * host, ENetPeer * peer, ENetEvent * event)
{
    host -> recalculateBandwidthLimits = 1;

    if (event == NULL)
       peer -> state = ENET_PEER_STATE_CONNECTION_PENDING;
    else
    {
       peer -> state = ENET_PEER_STATE_CONNECTED;

       event -> type = ENET_EVENT_TYPE_CONNECT;
       event -> peer = peer;
    }
}
