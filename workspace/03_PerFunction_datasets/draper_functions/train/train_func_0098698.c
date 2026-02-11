detect_link_ethtool(void)
{
	struct ifreq ifreq;
	struct ethtool_value edata;

	set_ifreq_to_ifname(&ifreq);

	edata.cmd = ETHTOOL_GLINK;
	ifreq.ifr_data = (void*) &edata;

	if (network_ioctl(SIOCETHTOOL, &ifreq, "ETHTOOL_GLINK") < 0) {
		return IFSTATUS_ERR;
	}

	return edata.data ? IFSTATUS_UP : IFSTATUS_DOWN;
}
