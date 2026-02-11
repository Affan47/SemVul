ath10k_htc_wait_target(struct ath10k_htc *htc)
{
	struct ath10k *ar = htc->ar;
	int i, status = 0;
	unsigned long time_left;
	struct ath10k_htc_svc_conn_req conn_req;
	struct ath10k_htc_svc_conn_resp conn_resp;
	struct ath10k_htc_msg *msg;
	u16 message_id;
	u16 credit_count;
	u16 credit_size;

	time_left = wait_for_completion_timeout(&htc->ctl_resp,
						ATH10K_HTC_WAIT_TIMEOUT_HZ);
	if (!time_left) {


		ath10k_warn(ar, "failed to receive control response completion, polling..\n");

		for (i = 0; i < CE_COUNT; i++)
			ath10k_hif_send_complete_check(htc->ar, i, 1);

		time_left =
		wait_for_completion_timeout(&htc->ctl_resp,
					    ATH10K_HTC_WAIT_TIMEOUT_HZ);

		if (!time_left)
			status = -ETIMEDOUT;
	}

	if (status < 0) {
		ath10k_err(ar, "ctl_resp never came in (%d)\n", status);
		return status;
	}

	if (htc->control_resp_len < sizeof(msg->hdr) + sizeof(msg->ready)) {
		ath10k_err(ar, "Invalid HTC ready msg len:%d\n",
			   htc->control_resp_len);
		return -ECOMM;
	}

	msg = (struct ath10k_htc_msg *)htc->control_resp_buffer;
	message_id   = __le16_to_cpu(msg->hdr.message_id);
	credit_count = __le16_to_cpu(msg->ready.credit_count);
	credit_size  = __le16_to_cpu(msg->ready.credit_size);

	if (message_id != ATH10K_HTC_MSG_READY_ID) {
		ath10k_err(ar, "Invalid HTC ready msg: 0x%x\n", message_id);
		return -ECOMM;
	}

	htc->total_transmit_credits = credit_count;
	htc->target_credit_size = credit_size;

	ath10k_dbg(ar, ATH10K_DBG_HTC,
		   "Target ready! transmit resources: %d size:%d\n",
		   htc->total_transmit_credits,
		   htc->target_credit_size);

	if ((htc->total_transmit_credits == 0) ||
	    (htc->target_credit_size == 0)) {
		ath10k_err(ar, "Invalid credit size received\n");
		return -ECOMM;
	}

	ath10k_htc_setup_target_buffer_assignments(htc);


	memset(&conn_req, 0, sizeof(conn_req));
	memset(&conn_resp, 0, sizeof(conn_resp));
	conn_req.ep_ops.ep_tx_complete = ath10k_htc_control_tx_complete;
	conn_req.ep_ops.ep_rx_complete = ath10k_htc_control_rx_complete;
	conn_req.max_send_queue_depth = ATH10K_NUM_CONTROL_TX_BUFFERS;
	conn_req.service_id = ATH10K_HTC_SVC_ID_RSVD_CTRL;


	status = ath10k_htc_connect_service(htc, &conn_req, &conn_resp);
	if (status) {
		ath10k_err(ar, "could not connect to htc service (%d)\n",
			   status);
		return status;
	}

	return 0;
}
