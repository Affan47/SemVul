ns_server_setdebuglevel(ns_server_t *server, char *args) {
	char *ptr;
	char *levelstr;
	char *endp;
	long newlevel;

	UNUSED(server);


	ptr = next_token(&args, " \t");
	if (ptr == NULL)
		return (ISC_R_UNEXPECTEDEND);


	levelstr = next_token(&args, " \t");
	if (levelstr == NULL) {
		if (ns_g_debuglevel < 99)
			ns_g_debuglevel++;
	} else {
		newlevel = strtol(levelstr, &endp, 10);
		if (*endp != '\0' || newlevel < 0 || newlevel > 99)
			return (ISC_R_RANGE);
		ns_g_debuglevel = (unsigned int)newlevel;
	}
	isc_log_setdebuglevel(ns_g_lctx, ns_g_debuglevel);
	isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL,
		      NS_LOGMODULE_SERVER, ISC_LOG_INFO,
		      "debug level is now %d", ns_g_debuglevel);
	return (ISC_R_SUCCESS);
}
