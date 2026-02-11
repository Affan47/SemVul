iscsi_tcp_data_recv_prep(struct iscsi_tcp_conn *tcp_conn)
{
	struct iscsi_conn *conn = tcp_conn->iscsi_conn;
	struct hash_desc *rx_hash = NULL;

	if (conn->datadgst_en &&
	    !(conn->session->tt->caps & CAP_DIGEST_OFFLOAD))
		rx_hash = tcp_conn->rx_hash;

	iscsi_segment_init_linear(&tcp_conn->in.segment,
				conn->data, tcp_conn->in.datalen,
				iscsi_tcp_data_recv_done, rx_hash);
}
