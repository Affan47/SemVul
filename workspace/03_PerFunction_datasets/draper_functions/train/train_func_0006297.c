dwceqos_get_sset_count(struct net_device *ndev, int sset)
{
	if (sset == ETH_SS_STATS)
		return ARRAY_SIZE(dwceqos_ethtool_stats);

	return -EOPNOTSUPP;
}
