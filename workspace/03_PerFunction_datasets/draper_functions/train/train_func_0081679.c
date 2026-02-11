isert_rdma_accept(struct isert_conn *isert_conn)
{
	struct rdma_cm_id *cm_id = isert_conn->cm_id;
	struct rdma_conn_param cp;
	int ret;

	memset(&cp, 0, sizeof(struct rdma_conn_param));
	cp.initiator_depth = isert_conn->initiator_depth;
	cp.retry_count = 7;
	cp.rnr_retry_count = 7;

	ret = rdma_accept(cm_id, &cp);
	if (ret) {
		isert_err("rdma_accept() failed with: %d\n", ret);
		return ret;
	}

	return 0;
}
