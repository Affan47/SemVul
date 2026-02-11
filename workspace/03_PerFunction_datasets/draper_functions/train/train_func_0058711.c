beiscsi_conn_start(struct iscsi_cls_conn *cls_conn)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct beiscsi_conn *beiscsi_conn = conn->dd_data;
	struct beiscsi_endpoint *beiscsi_ep;
	struct beiscsi_offload_params params;
	struct beiscsi_hba *phba;

	phba = ((struct beiscsi_conn *)conn->dd_data)->phba;

	if (phba->state & BE_ADAPTER_PCI_ERR) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : In PCI_ERROR Recovery\n");
		return -EBUSY;
	} else {
		beiscsi_log(beiscsi_conn->phba, KERN_INFO,
			    BEISCSI_LOG_CONFIG,
			    "BS_%d : In beiscsi_conn_start\n");
	}

	memset(&params, 0, sizeof(struct beiscsi_offload_params));
	beiscsi_ep = beiscsi_conn->ep;
	if (!beiscsi_ep)
		beiscsi_log(beiscsi_conn->phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG,
			    "BS_%d : In beiscsi_conn_start , no beiscsi_ep\n");

	beiscsi_conn->login_in_progress = 0;
	beiscsi_set_params_for_offld(beiscsi_conn, &params);
	beiscsi_offload_connection(beiscsi_conn, &params);
	iscsi_conn_start(cls_conn);
	return 0;
}
