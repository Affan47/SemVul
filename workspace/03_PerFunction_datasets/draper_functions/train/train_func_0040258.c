req_set_stat(struct rad_req_t *req, struct ap_session *ses)
{
	struct rtnl_link_stats stats;
	struct radius_pd_t *rpd = req->rpd;
	struct timespec ts;
	int ret = 0;

	if (ses->stop_time)
		ts.tv_sec = ses->stop_time;
	else
		clock_gettime(CLOCK_MONOTONIC, &ts);

	if (ap_session_read_stats(ses, &stats) == 0) {
		rad_packet_change_int(req->pack, NULL, "Acct-Input-Octets", stats.rx_bytes);
		rad_packet_change_int(req->pack, NULL, "Acct-Output-Octets", stats.tx_bytes);
		rad_packet_change_int(req->pack, NULL, "Acct-Input-Packets", stats.rx_packets);
		rad_packet_change_int(req->pack, NULL, "Acct-Output-Packets", stats.tx_packets);
		rad_packet_change_int(req->pack, NULL, "Acct-Input-Gigawords", rpd->ses->acct_input_gigawords);
		rad_packet_change_int(req->pack, NULL, "Acct-Output-Gigawords", rpd->ses->acct_output_gigawords);
	} else
		ret = -1;

	rad_packet_change_int(req->pack, NULL, "Acct-Session-Time", ts.tv_sec - ses->start_time);

	return ret;
}
