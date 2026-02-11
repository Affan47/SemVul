update_stats(struct connman_ipdevice *ipdevice,
						struct rtnl_link_stats *stats)
{
	struct connman_service *service;

	if (stats->rx_packets == 0 && stats->tx_packets == 0)
		return;

	connman_info("%s {RX} %u packets %u bytes", ipdevice->ifname,
					stats->rx_packets, stats->rx_bytes);
	connman_info("%s {TX} %u packets %u bytes", ipdevice->ifname,
					stats->tx_packets, stats->tx_bytes);

	if (ipdevice->config_ipv4 == NULL && ipdevice->config_ipv6 == NULL)
		return;

	if (ipdevice->config_ipv4)
		service = __connman_ipconfig_get_data(ipdevice->config_ipv4);
	else if (ipdevice->config_ipv6)
		service = __connman_ipconfig_get_data(ipdevice->config_ipv6);
	else
		return;

	if (service == NULL)
		return;

	ipdevice->rx_packets = stats->rx_packets;
	ipdevice->tx_packets = stats->tx_packets;
	ipdevice->rx_bytes = stats->rx_bytes;
	ipdevice->tx_bytes = stats->tx_bytes;
	ipdevice->rx_errors = stats->rx_errors;
	ipdevice->tx_errors = stats->tx_errors;
	ipdevice->rx_dropped = stats->rx_dropped;
	ipdevice->tx_dropped = stats->tx_dropped;

	__connman_service_notify(service,
				ipdevice->rx_packets, ipdevice->tx_packets,
				ipdevice->rx_bytes, ipdevice->tx_bytes,
				ipdevice->rx_errors, ipdevice->tx_errors,
				ipdevice->rx_dropped, ipdevice->tx_dropped);
}
