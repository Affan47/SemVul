enet_host_broadcast (ENetHost * host, enet_uint8 channelID, ENetPacket * packet)
{
    ENetPeer * currentPeer;

    for (currentPeer = host -> peers;
         currentPeer < & host -> peers [host -> peerCount];
         ++ currentPeer)
    {
       if (currentPeer -> state != ENET_PEER_STATE_CONNECTED)
         continue;

       enet_peer_send (currentPeer, channelID, packet);
    }

    if (packet -> referenceCount == 0)
      enet_packet_destroy (packet);
}
