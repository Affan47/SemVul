enet_peer_throttle (ENetPeer * peer, enet_uint32 rtt)
{
    if (peer -> lastRoundTripTime <= peer -> lastRoundTripTimeVariance)
    {
        peer -> packetThrottle = peer -> packetThrottleLimit;
    }
    else
    if (rtt < peer -> lastRoundTripTime)
    {
        peer -> packetThrottle += peer -> packetThrottleAcceleration;

        if (peer -> packetThrottle > peer -> packetThrottleLimit)
          peer -> packetThrottle = peer -> packetThrottleLimit;

        return 1;
    }
    else
    if (rtt > peer -> lastRoundTripTime + 2 * peer -> lastRoundTripTimeVariance)
    {
        if (peer -> packetThrottle > peer -> packetThrottleDeceleration)
          peer -> packetThrottle -= peer -> packetThrottleDeceleration;
        else
          peer -> packetThrottle = 0;

        return -1;
    }

    return 0;
}
