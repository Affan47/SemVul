enet_protocol_handle_send_unreliable (ENetHost * host, ENetPeer * peer, const ENetProtocol * command)
{
    ENetPacket * packet;

    if (command -> header.commandLength <= sizeof (ENetProtocolSendUnreliable) ||
        command -> header.channelID >= peer -> channelCount ||
        peer -> state != ENET_PEER_STATE_CONNECTED)
      return;

    packet = enet_packet_create ((const enet_uint8 *) command + sizeof (ENetProtocolSendUnreliable),
                                 command -> header.commandLength - sizeof (ENetProtocolSendUnreliable),
                                 0);

    enet_peer_queue_incoming_command (peer, command, packet, 0);
}
