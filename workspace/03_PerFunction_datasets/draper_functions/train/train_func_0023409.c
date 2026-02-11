iser_post_rx_bufs(struct iscsi_conn *conn, struct iscsi_hdr *req)
{
	struct iser_conn *iser_conn = conn->dd_data;
	struct ib_conn *ib_conn = &iser_conn->ib_conn;
	struct iscsi_session *session = conn->session;

	iser_dbg("req op %x flags %x\n", req->opcode, req->flags);

	if ((req->flags & ISCSI_FULL_FEATURE_PHASE) != ISCSI_FULL_FEATURE_PHASE)
		return 0;


	WARN_ON(ib_conn->post_recv_buf_count != 1);

	if (session->discovery_sess) {
		iser_info("Discovery session, re-using login RX buffer\n");
		return 0;
	} else
		iser_info("Normal session, posting batch of RX %d buffers\n",
			  iser_conn->min_posted_rx);


	if (iser_post_recvm(iser_conn, iser_conn->min_posted_rx))
		return -ENOMEM;

	return 0;
}
