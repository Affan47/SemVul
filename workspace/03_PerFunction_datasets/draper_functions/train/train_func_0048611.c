iscsi_target_check_for_existing_instances(
	struct iscsi_conn *conn,
	struct iscsi_login *login)
{
	if (login->checked_for_existing)
		return 0;

	login->checked_for_existing = 1;

	if (!login->tsih)
		return iscsi_check_for_session_reinstatement(conn);
	else
		return iscsi_login_post_auth_non_zero_tsih(conn, login->cid,
				login->initial_exp_statsn);
}
