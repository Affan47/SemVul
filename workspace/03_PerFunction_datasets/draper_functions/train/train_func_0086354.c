find_request_by_storage(void *parent, enum cm_tdbus_type bus,
			const char *dbdir,
			const char *nickname,
			const char *token,
			const char *certfile,
			int verbose)
{
	char **requests;
	int i, which;
	char *cert_stype, *cert_sloc, *cert_nick, *cert_tok;
	requests = query_rep_ap(bus, CM_DBUS_BASE_PATH, CM_DBUS_BASE_INTERFACE,
				"get_requests", verbose, globals.tctx);
	which = -1;
	for (i = 0; (requests != NULL) && (requests[i] != NULL); i++) {
		query_rep_sososos(bus, requests[i],
				  CM_DBUS_REQUEST_INTERFACE,
				  "get_cert_storage_info",
				  verbose, parent,
				  &cert_stype, &cert_sloc,
				  &cert_nick, &cert_tok);
		if (strcasecmp(cert_stype, "NSSDB") == 0) {
			if (dbdir == NULL) {
				continue;
			}
			if ((cert_sloc == NULL) ||
			    (strcmp(dbdir, cert_sloc) != 0)) {
				continue;
			}
			if (nickname == NULL) {
				continue;
			}
			if ((cert_nick == NULL) ||
			    (strcmp(nickname, cert_nick) != 0)) {
				continue;
			}
			if ((token != NULL) &&
			    ((cert_tok == NULL) ||
			     (strcmp(token, cert_tok) != 0))) {
				continue;
			}
		} else
		if (strcasecmp(cert_stype, "FILE") == 0) {
			if (certfile == NULL) {
				continue;
			}
			if (strcmp(certfile, cert_sloc) != 0) {
				continue;
			}
		}
		if (which != -1) {

			return NULL;
		}
		which = i;
	}
	if (which != -1) {
		return requests[which];
	}
	return NULL;
}
