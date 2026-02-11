iscsi_iser_ep_connect(struct Scsi_Host *shost, struct sockaddr *dst_addr,
		      int non_blocking)
{
	int err;
	struct iser_conn *iser_conn;
	struct iscsi_endpoint *ep;

	ep = iscsi_create_endpoint(0);
	if (!ep)
		return ERR_PTR(-ENOMEM);

	iser_conn = kzalloc(sizeof(*iser_conn), GFP_KERNEL);
	if (!iser_conn) {
		err = -ENOMEM;
		goto failure;
	}

	ep->dd_data = iser_conn;
	iser_conn->ep = ep;
	iser_conn_init(iser_conn);

	err = iser_connect(iser_conn, NULL, dst_addr, non_blocking);
	if (err)
		goto failure;

	return ep;
failure:
	iscsi_destroy_endpoint(ep);
	return ERR_PTR(err);
}
