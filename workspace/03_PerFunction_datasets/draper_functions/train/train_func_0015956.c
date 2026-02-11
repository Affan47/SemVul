gfarm_ldap_session_error(void)
{
	int e;
	int rv = ldap_get_option(gfarm_ldap_server, LDAP_OPT_RESULT_CODE, &e);

	if (rv != LDAP_OPT_SUCCESS)
		gflog_fatal(GFARM_MSG_1002362, "ldap_get_option: %d", rv);

	return (ldap_err2string(e));
}
