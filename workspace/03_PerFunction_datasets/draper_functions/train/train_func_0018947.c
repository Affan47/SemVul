gfire_get_name(const gfire_data *p_gfire)
{
	if(!p_gfire)
		return NULL;

	return purple_account_get_username(purple_connection_get_account(gfire_get_connection(p_gfire)));
}
