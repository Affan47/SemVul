ldapsrv_set_options (gint secs, LDAP *ld)
{
	static struct timeval timeout;
	int rc;
	int i;
	timeout.tv_sec = secs;
	timeout.tv_usec = 0;
#ifdef G_OS_UNIX
	i = LDAP_OPT_X_TLS_ALLOW;
	rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_REQUIRE_CERT, &i);
	if (ld)
		debug_print("cert %s\n", ldaputil_get_error(ld));
	else
		debug_print("cert %s\n", ldap_err2string(rc));

	rc = ldap_set_option(NULL, LDAP_OPT_NETWORK_TIMEOUT, &timeout);
	if (ld)
		debug_print("tm %s\n", ldaputil_get_error(ld));
	else
		debug_print("tm %s\n", ldap_err2string(rc));
#endif
}
