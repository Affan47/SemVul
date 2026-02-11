createCASCookie(request_rec *r, char *user, cas_saml_attr *attrs, char *ticket)
{
	char *path, *buf, *rv;
	apr_file_t *f;
	cas_cache_entry e;
	int i;
	cas_cfg *c = ap_get_module_config(r->server->module_config, &auth_cas_module);
	cas_dir_cfg *d = ap_get_module_config(r->per_dir_config, &auth_cas_module);
	buf = apr_pcalloc(r->pool, c->CASCookieEntropy);

	if(c->CASDebug)
		ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "entering createCASCookie()");

	CASCleanCache(r, c);

	e.user = user;
	e.issued = apr_time_now();
	e.lastactive = apr_time_now();
	e.path = getCASPath(r);
	e.renewed = (d->CASRenew == NULL ? 0 : 1);
	e.secure = (isSSL(r) == TRUE ? 1 : 0);
	e.ticket = ticket;
	e.attrs = attrs;


	apr_generate_random_bytes((unsigned char *) buf, c->CASCookieEntropy);
	rv = (char *) ap_md5_binary(r->pool, (unsigned char *) buf, c->CASCookieEntropy);


	if(writeCASCacheEntry(r, rv, &e, FALSE) == FALSE)
		return NULL;

	if(c->CASDebug)
		ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "Cookie '%s' created for user '%s'", rv, user);

	buf = (char *) ap_md5_binary(r->pool, (const unsigned char *) ticket, (int) strlen(ticket));
	path = apr_psprintf(r->pool, "%s.%s", c->CASCookiePath, buf);

	if((i = apr_file_open(&f, path, APR_FOPEN_CREATE|APR_FOPEN_WRITE|APR_EXCL, APR_FPROT_UREAD|APR_FPROT_UWRITE, r->pool)) != APR_SUCCESS) {
		ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "MOD_AUTH_CAS: Service Ticket to Cookie map file '%s' could not be created: %s", path, apr_strerror(i, buf, strlen(buf)));
		return FALSE;
	} else {
		apr_file_printf(f, "%s", rv);
		apr_file_close(f);
	}

	return(apr_pstrdup(r->pool, rv));
}
