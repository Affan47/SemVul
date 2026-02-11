xmlrpcmethod_logout(void *conn, int parc, char *parv[])
{
	authcookie_t *ac;
	myuser_t *mu;

	if (parc < 2)
	{
		xmlrpc_generic_error(fault_needmoreparams, "Insufficient parameters.");
		return 0;
	}

	if ((mu = myuser_find(parv[1])) == NULL)
	{
		xmlrpc_generic_error(fault_nosuch_source, "Unknown user.");
		return 0;
	}

	if (authcookie_validate(parv[0], mu) == false)
	{
		xmlrpc_generic_error(fault_badauthcookie, "Invalid authcookie for this account.");
		return 0;
	}

	logcommand_external(nicksvs.me, "xmlrpc", conn, NULL, mu, CMDLOG_LOGIN, "LOGOUT");

	ac = authcookie_find(parv[0], mu);
	authcookie_destroy(ac);

	xmlrpc_send_string("You are now logged out.");

	return 0;
}
