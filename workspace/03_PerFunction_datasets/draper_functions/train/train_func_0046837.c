iscsi_target_do_tx_login_io(struct iscsi_conn *conn, struct iscsi_login *login)
{
	u32 padding = 0;
	struct iscsi_login_rsp *login_rsp;

	login_rsp = (struct iscsi_login_rsp *) login->rsp;

	login_rsp->opcode		= ISCSI_OP_LOGIN_RSP;
	hton24(login_rsp->dlength, login->rsp_length);
	memcpy(login_rsp->isid, login->isid, 6);
	login_rsp->tsih			= cpu_to_be16(login->tsih);
	login_rsp->itt			= login->init_task_tag;
	login_rsp->statsn		= cpu_to_be32(conn->stat_sn++);
	login_rsp->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	login_rsp->max_cmdsn		= cpu_to_be32((u32) atomic_read(&conn->sess->max_cmd_sn));

	pr_debug("Sending Login Response, Flags: 0x%02x, ITT: 0x%08x,"
		" ExpCmdSN; 0x%08x, MaxCmdSN: 0x%08x, StatSN: 0x%08x, Length:"
		" %u\n", login_rsp->flags, (__force u32)login_rsp->itt,
		ntohl(login_rsp->exp_cmdsn), ntohl(login_rsp->max_cmdsn),
		ntohl(login_rsp->statsn), login->rsp_length);

	padding = ((-login->rsp_length) & 3);


	if (login->login_complete) {
		int rc = iscsit_start_kthreads(conn);
		if (rc) {
			iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
					    ISCSI_LOGIN_STATUS_NO_RESOURCES);
			return -1;
		}
	}

	if (conn->conn_transport->iscsit_put_login_tx(conn, login,
					login->rsp_length + padding) < 0)
		goto err;

	login->rsp_length		= 0;

	return 0;

err:
	if (login->login_complete) {
		if (conn->rx_thread && conn->rx_thread_active) {
			send_sig(SIGINT, conn->rx_thread, 1);
			complete(&conn->rx_login_comp);
			kthread_stop(conn->rx_thread);
		}
		if (conn->tx_thread && conn->tx_thread_active) {
			send_sig(SIGINT, conn->tx_thread, 1);
			kthread_stop(conn->tx_thread);
		}
		spin_lock(&iscsit_global->ts_bitmap_lock);
		bitmap_release_region(iscsit_global->ts_bitmap, conn->bitmap_id,
				      get_order(1));
		spin_unlock(&iscsit_global->ts_bitmap_lock);
	}
	return -1;
}
