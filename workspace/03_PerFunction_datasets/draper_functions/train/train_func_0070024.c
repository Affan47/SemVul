getCASScope(request_rec *r)
{
	char *rv = NULL, *requestPath = getCASPath(r);
	cas_cfg *c = ap_get_module_config(r->server->module_config, &auth_cas_module);
	cas_dir_cfg *d = ap_get_module_config(r->per_dir_config, &auth_cas_module);

	if(c->CASDebug)
		ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "Determining CAS scope (path: %s, CASScope: %s, CASRenew: %s, CASGateway: %s)", requestPath, d->CASScope, d->CASRenew, d->CASGateway);

	if (d->CASGateway != NULL) {

		if(strncmp(d->CASGateway, requestPath, strlen(d->CASGateway)) == 0)
			rv = d->CASGateway;
		else {
			ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "MOD_AUTH_CAS: CASGateway (%s) not a substring of request path, using request path (%s) for cookie", d->CASGateway, requestPath);
			rv = requestPath;
		}
	}

	if(d->CASRenew != NULL) {
		if(rv != NULL) {
			ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "MOD_AUTH_CAS: CASRenew (%s) and CASGateway (%s) set, CASRenew superceding.", d->CASRenew, d->CASGateway);
		}
		if(strncmp(d->CASRenew, requestPath, strlen(d->CASRenew)) == 0)
			rv = d->CASRenew;
		else {
			ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "MOD_AUTH_CAS: CASRenew (%s) not a substring of request path, using request path (%s) for cookie", d->CASRenew, requestPath);
			rv = requestPath;
		}

	}


	if(rv == NULL) {
		if(d->CASScope != NULL) {
			if(strncmp(d->CASScope, requestPath, strlen(d->CASScope)) == 0)
				rv = d->CASScope;
			else {
				ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "MOD_AUTH_CAS: CASScope (%s) not a substring of request path, using request path (%s) for cookie", d->CASScope, requestPath);
				rv = requestPath;
			}
		}
		else
			rv = requestPath;
	}

	return (rv);
}
