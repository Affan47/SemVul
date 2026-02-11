igbvf_get_ethtool_stats(struct net_device *netdev,
				    struct ethtool_stats *stats,
				    u64 *data)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	int i;

	igbvf_update_stats(adapter);
	for (i = 0; i < IGBVF_GLOBAL_STATS_LEN; i++) {
		char *p = (char *)adapter +
			  igbvf_gstrings_stats[i].stat_offset;
		char *b = (char *)adapter +
			  igbvf_gstrings_stats[i].base_stat_offset;
		data[i] = ((igbvf_gstrings_stats[i].sizeof_stat ==
			    sizeof(u64)) ? (*(u64 *)p - *(u64 *)b) :
			    (*(u32 *)p - *(u32 *)b));
	}
}
