enet_protocol_dispatch_incoming_commands (ENetHost * host, ENetEvent * event)
{
    ENetPeer * currentPeer = host -> lastServicedPeer;
    ENetChannel * channel;

    do
    {
       ++ currentPeer;

       if (currentPeer >= & host -> peers [host -> peerCount])
         currentPeer = host -> peers;

       switch (currentPeer -> state)
       {
       case ENET_PEER_STATE_CONNECTION_PENDING:
           currentPeer -> state = ENET_PEER_STATE_CONNECTED;

           event -> type = ENET_EVENT_TYPE_CONNECT;
           event -> peer = currentPeer;

           return 1;

       case ENET_PEER_STATE_ZOMBIE:
           host -> recalculateBandwidthLimits = 1;

           event -> type = ENET_EVENT_TYPE_DISCONNECT;
           event -> peer = currentPeer;
           event -> data = currentPeer -> disconnectData;

           enet_peer_reset (currentPeer);

           host -> lastServicedPeer = currentPeer;

           return 1;
       }

       if (currentPeer -> state != ENET_PEER_STATE_CONNECTED)
         continue;

       for (channel = currentPeer -> channels;
            channel < & currentPeer -> channels [currentPeer -> channelCount];
            ++ channel)
       {
           if (enet_list_empty (& channel -> incomingReliableCommands) &&
               enet_list_empty (& channel -> incomingUnreliableCommands))
             continue;

           event -> packet = enet_peer_receive (currentPeer, channel - currentPeer -> channels);
           if (event -> packet == NULL)
             continue;

           event -> type = ENET_EVENT_TYPE_RECEIVE;
           event -> peer = currentPeer;
           event -> channelID = (enet_uint8) (channel - currentPeer -> channels);

           host -> lastServicedPeer = currentPeer;

           return 1;
       }
    } while (currentPeer != host -> lastServicedPeer);

    return 0;
}
