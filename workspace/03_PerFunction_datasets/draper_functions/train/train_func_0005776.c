send_tcp(struct mux_connection *conn, uint8_t flags, const unsigned char *data, int length)
{
	struct tcphdr th;
	memset(&th, 0, sizeof(th));
	th.th_sport = htons(conn->sport);
	th.th_dport = htons(conn->dport);
	th.th_seq = htonl(conn->tx_seq);
	th.th_ack = htonl(conn->tx_ack);
	th.th_flags = flags;
	th.th_off = sizeof(th) / 4;
	th.th_win = htons(conn->tx_win >> 8);

	usbmuxd_log(LL_DEBUG, "[OUT] dev=%d sport=%d dport=%d seq=%d ack=%d flags=0x%x window=%d[%d] len=%d",
		conn->dev->id, conn->sport, conn->dport, conn->tx_seq, conn->tx_ack, flags, conn->tx_win, conn->tx_win >> 8, length);

	int res = send_packet(conn->dev, MUX_PROTO_TCP, &th, data, length);
	if(res >= 0) {
		conn->tx_acked = conn->tx_ack;
		conn->last_ack_time = mstime64();
		conn->flags &= ~CONN_ACK_PENDING;
	}
	return res;
}
