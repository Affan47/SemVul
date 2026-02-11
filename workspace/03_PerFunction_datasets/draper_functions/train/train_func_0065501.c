setContext(SPtr<TDUID> srvDuid, SPtr<TIPv6Addr> srvAddr,
                               TMsg * originalMsg)
{
    DUID=srvDuid;
    if (srvAddr) {
        Unicast = true;
    } else {
        Unicast = false;
    }
    Prefix = srvAddr;
    OriginalMsg = originalMsg;
    Iface = originalMsg->getIface();
}
