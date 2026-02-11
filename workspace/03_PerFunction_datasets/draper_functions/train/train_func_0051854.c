isert_get_login_rx(struct iscsi_conn *conn, struct iscsi_login *login)
{
	struct isert_conn *isert_conn = conn->context;
	int ret;

	isert_info("before login_req comp conn: %p\n", isert_conn);
	ret = wait_for_completion_interruptible(&isert_conn->login_req_comp);
	if (ret) {
		isert_err("isert_conn %p interrupted before got login req\n",
			  isert_conn);
		return ret;
	}
	reinit_completion(&isert_conn->login_req_comp);


	if (!login->first_request)
		return 0;

	isert_rx_login_req(isert_conn);

	isert_info("before login_comp conn: %p\n", conn);
	ret = wait_for_completion_interruptible(&isert_conn->login_comp);
	if (ret)
		return ret;

	isert_info("processing login->req: %p\n", login->req);

	return 0;
}
