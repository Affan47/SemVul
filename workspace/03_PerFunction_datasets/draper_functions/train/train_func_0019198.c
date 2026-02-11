gfire_wants_server_detection(const gfire_data *p_gfire)
{
	return (p_gfire && p_gfire->gc && purple_account_get_bool(purple_connection_get_account(p_gfire->gc),
															  "server_detection_option", FALSE));
}
