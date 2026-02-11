ap_session_set_ifindex(struct ap_session *ses)
{
	struct rtnl_link_stats stats;

	if (iplink_get_stats(ses->ifindex, &stats))
		log_ppp_warn("failed to get interface statistics\n");
	else {
		ses->acct_rx_packets_i = stats.rx_packets;
		ses->acct_tx_packets_i = stats.tx_packets;
		ses->acct_rx_bytes_i = stats.rx_bytes;
		ses->acct_tx_bytes_i = stats.tx_bytes;
	}
}
