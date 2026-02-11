mysasl_authproc(sasl_conn_t *conn,
		void *context,
		const char *requested_user, unsigned rlen,
		const char *auth_identity, unsigned alen,
		const char *def_realm, unsigned urlen,
		struct propctx *propctx)
{
    char replybuf[150];
    char *realm;


    if (realm = strchr(auth_identity, '@')) {
	realm++;
	if (!option_lookup("", opt_login_realms, 1, realm)) {
	    snprintf(replybuf, sizeof(replybuf),
		     err_nocrossrealm, auth_identity);
	    sasl_seterror(conn, 0, replybuf);
	    return SASL_BADAUTH;
	}
    }

    if (strcmp(auth_identity, requested_user)) {

	if (option_lookup("", opt_alladmin, 1, auth_identity)) {
	    return SASL_OK;
	} else {

	    sasl_seterror(conn, 0, err_noproxy);
	    return SASL_BADAUTH;
	}
    }

    return SASL_OK;
}
