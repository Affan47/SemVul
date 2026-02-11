isert_conn_terminate(struct isert_conn *isert_conn)
{
	int err;

	if (isert_conn->state >= ISER_CONN_TERMINATING)
		return;

	isert_info("Terminating conn %p state %d\n",
		   isert_conn, isert_conn->state);
	isert_conn->state = ISER_CONN_TERMINATING;
	err = rdma_disconnect(isert_conn->cm_id);
	if (err)
		isert_warn("Failed rdma_disconnect isert_conn %p\n",
			   isert_conn);

	isert_info("conn %p completing wait\n", isert_conn);
	complete(&isert_conn->wait);
}
