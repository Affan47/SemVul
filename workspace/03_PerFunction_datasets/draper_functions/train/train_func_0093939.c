incrPrefixCount(int ifindex, SPtr<TIPv6Addr> prefix)
{
    SPtr<TSrvCfgIface> iface;
    iface = getIfaceByID(ifindex);
    if (!iface) {
	Log(Error) << "Unable to find interface with ifindex=" << ifindex << ", prefix increase count aborted." << LogEnd;
	return false;
    }
    return iface->addClntPrefix(prefix);
}
