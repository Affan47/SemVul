connman_session_parse_bearers(const char *token, GSList **list)
{
	enum connman_service_type bearer;
	int err;

	if (g_strcmp0(token, "") == 0)
		return 0;

	err = bearer2service(token, &bearer);
	if (err < 0)
		return err;

	*list = g_slist_append(*list, GINT_TO_POINTER(bearer));

	return 0;
}
