enet_peer_timeout (ENetPeer * peer, enet_uint32 timeoutLimit, enet_uint32 timeoutMinimum, enet_uint32 timeoutMaximum)
{
    peer -> timeoutLimit = timeoutLimit ? timeoutLimit : ENET_PEER_TIMEOUT_LIMIT;
    peer -> timeoutMinimum = timeoutMinimum ? timeoutMinimum : ENET_PEER_TIMEOUT_MINIMUM;
    peer -> timeoutMaximum = timeoutMaximum ? timeoutMaximum : ENET_PEER_TIMEOUT_MAXIMUM;
}
