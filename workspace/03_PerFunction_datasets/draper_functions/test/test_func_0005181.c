need_read_write_negative(struct conn_info *ci)
{
	struct tcp_spec ts;
	char buf[1400];
	int len;


	if (need_read > 0 && need_write > 0)
		return;
	if (need_read_want_n > need_read || need_write_want_n > need_write)
		return;
	if (need_read < need_write)
		len = -need_read;
	else
		len = -need_write;
	if (len > sizeof(buf))
		len = sizeof(buf);
	memset(buf, ' ', len);
	ts.saddr = ci->src_addr;
	ts.daddr = ci->dst_addr;
	ts.sport = ci->src_port;
	ts.dport = ci->dst_port;
	ts.src_mac = ci->dst.dst_mac;
	ts.dst_mac = ci->dst.src_mac;
	ts.seq = ci->dst.next_d_seq;
	ts.ack_seq = ci->dst.next_seq;
	ts.window = ci->src.window ? ci->src.window : htons(242);
	ts.ack = 1;
	ts.psh = 1;
	ts.rst = 0;
	ts.data = buf;
	ts.data_len = len;
	send_tcp_packet(&ts);
	need_read += len;
	need_write += len;
	need_read_want_n = need_read;
	need_write_want_n = need_write;
}
