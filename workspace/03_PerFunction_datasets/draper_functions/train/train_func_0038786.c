enet_peer_ping (ENetPeer * peer)
{
    ENetProtocol command;

    if (peer -> state != ENET_PEER_STATE_CONNECTED)
      return;

    command.header.command = ENET_PROTOCOL_COMMAND_PING;
    command.header.channelID = 0xFF;
    command.header.flags = ENET_PROTOCOL_FLAG_ACKNOWLEDGE;
    command.header.commandLength = sizeof (ENetProtocolPing);

    enet_peer_queue_outgoing_command (peer, & command, NULL, 0, 0);
}
