ext_msn_connect(MsnConnection *mc, MsnConnectionCallback callback)
{
	int tag;

	struct ay_msn_cbdata *data = g_new0(struct ay_msn_cbdata, 1);
	ay_msn_local_account *mlad;
	eb_local_account *ela;

	data->mc = mc;
	data->callback = callback;

	ela = (eb_local_account *)mc->account->ext_data;
	mlad = (ay_msn_local_account *)ela->protocol_local_account_data;


	if (!ela->connecting && !ela->connected)
		return;

	AyConnection *fd =
		ay_connection_new(mc->host, mc->port,
		(mc->use_ssl ? AY_CONNECTION_TYPE_SSL :
			AY_CONNECTION_TYPE_PLAIN));

	tag = ay_connection_connect(fd, ay_msn_connected, ay_msn_connect_status,
		eb_do_confirm_dialog, data);

	if (tag < 0) {
		char buff[1024];
		snprintf(buff, sizeof(buff), _("Cannot connect to %s."),
			mc->host);
		ay_do_error(_("MSN Error"), buff);
		eb_debug(DBG_MSN, "%s\n", buff);
		ay_activity_bar_remove(mlad->activity_tag);
		mlad->activity_tag = 0;
		ela->connecting = 0;
		ay_msn_logout(ela);
		return;
	}

	if (mc->type == MSN_CONNECTION_NS)
		mlad->connect_tag = tag;

	mc->tag_c = tag;
}
