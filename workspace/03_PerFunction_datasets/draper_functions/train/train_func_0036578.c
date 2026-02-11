iscsi_tcp_hdr_recv_prep(struct iscsi_tcp_conn *tcp_conn)
{
	ISCSI_DBG_TCP(tcp_conn->iscsi_conn,
		      "(%s)\n", tcp_conn->iscsi_conn->hdrdgst_en ?
		      "digest enabled" : "digest disabled");
	iscsi_segment_init_linear(&tcp_conn->in.segment,
				tcp_conn->in.hdr_buf, sizeof(struct iscsi_hdr),
				iscsi_tcp_hdr_recv_done, NULL);
}
