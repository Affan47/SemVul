apply_params(struct node_rec *rec)
{
	struct user_param *param;
	int rc;


	rec->session.initial_login_retry_max = -1;
	rec->conn[0].timeo.noop_out_interval = -1;
	rec->conn[0].timeo.noop_out_timeout = -1;

	list_for_each_entry(param, &user_params, list) {


		if (!strcmp(param->name, IFACE_NETNAME)) {

			memset(rec->iface.hwaddress, 0,
				sizeof(rec->iface.hwaddress));
		} else if (!strcmp(param->name, IFACE_HWADDR)) {

			memset(rec->iface.netdev, 0, sizeof(rec->iface.netdev));
		} else if (!strcmp(param->name, IFACE_TRANSPORTNAME)) {


			memset(&rec->iface, 0, sizeof(rec->iface));
			iface_setup_defaults(&rec->iface);
		}
	}

	rc = idbm_node_set_rec_from_param(&user_params, rec, 0);
	if (rc)
		return rc;


	if (rec->session.initial_login_retry_max == -1)
		rec->session.initial_login_retry_max = 30;

	if (rec->conn[0].timeo.noop_out_interval == -1)
		rec->conn[0].timeo.noop_out_interval = 0;
	if (rec->conn[0].timeo.noop_out_timeout == -1)
		rec->conn[0].timeo.noop_out_timeout = 0;

	return 0;
}
