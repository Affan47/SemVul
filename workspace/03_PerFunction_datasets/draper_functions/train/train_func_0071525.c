enet_protocol_handle_throttle_configure (ENetHost * host, ENetPeer * peer, const ENetProtocol * command)
{
    if (peer -> state != ENET_PEER_STATE_CONNECTED && peer -> state != ENET_PEER_STATE_DISCONNECT_LATER)
      return -1;

    peer -> packetThrottleInterval = ENET_NET_TO_HOST_32 (command -> throttleConfigure.packetThrottleInterval);
    peer -> packetThrottleAcceleration = ENET_NET_TO_HOST_32 (command -> throttleConfigure.packetThrottleAcceleration);
    peer -> packetThrottleDeceleration = ENET_NET_TO_HOST_32 (command -> throttleConfigure.packetThrottleDeceleration);

    return 0;
}
