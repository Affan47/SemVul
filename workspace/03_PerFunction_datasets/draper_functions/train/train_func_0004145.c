beiscsi_ep_disconnect(struct iscsi_endpoint *ep)
{
	struct beiscsi_conn *beiscsi_conn;
	struct beiscsi_endpoint *beiscsi_ep;
	struct beiscsi_hba *phba;
	unsigned int tag;
	uint8_t mgmt_invalidate_flag, tcp_upload_flag;
	unsigned short savecfg_flag = CMD_ISCSI_SESSION_SAVE_CFG_ON_FLASH;

	beiscsi_ep = ep->dd_data;
	phba = beiscsi_ep->phba;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_ep_disconnect for ep_cid = %d\n",
		    beiscsi_ep->ep_cid);

	if (beiscsi_ep->conn) {
		beiscsi_conn = beiscsi_ep->conn;
		iscsi_suspend_queue(beiscsi_conn->conn);
		mgmt_invalidate_flag = ~BEISCSI_NO_RST_ISSUE;
		tcp_upload_flag = CONNECTION_UPLOAD_GRACEFUL;
	} else {
		mgmt_invalidate_flag = BEISCSI_NO_RST_ISSUE;
		tcp_upload_flag = CONNECTION_UPLOAD_ABORT;
	}

	if (phba->state & BE_ADAPTER_PCI_ERR) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : PCI_ERROR Recovery\n");
		goto free_ep;
	}

	tag = mgmt_invalidate_connection(phba, beiscsi_ep,
					  beiscsi_ep->ep_cid,
					  mgmt_invalidate_flag,
					  savecfg_flag);
	if (!tag) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : mgmt_invalidate_connection Failed for cid=%d\n",
			    beiscsi_ep->ep_cid);
	}

	beiscsi_mccq_compl(phba, tag, NULL, NULL);
	beiscsi_close_conn(beiscsi_ep, tcp_upload_flag);
free_ep:
	msleep(BEISCSI_LOGOUT_SYNC_DELAY);
	beiscsi_free_ep(beiscsi_ep);
	beiscsi_unbind_conn_to_cid(phba, beiscsi_ep->ep_cid);
	iscsi_destroy_endpoint(beiscsi_ep->openiscsi_ep);
}
