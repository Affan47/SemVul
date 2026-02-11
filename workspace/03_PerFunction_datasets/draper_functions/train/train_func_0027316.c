mysql_authenticate_basic_user(request_rec *r)
{
	mysql_auth_config_rec *sec = (mysql_auth_config_rec *) ap_get_module_config(r->per_dir_config, &auth_mysql_module);
	conn_rec *c = r->connection;
	const char *sent_pw;
	int res;

	APACHELOG(APLOG_DEBUG, r, "Handling an authentication request for section %s", sec->dir);

#ifdef DEBUG
	for (res = 0; res < 512; res++)
	{
		if (sec->sacrificial_lamb[res] == '\0')
		{
			sec->sacrificial_lamb[res] = 'n';
		}
		if (!isgraph(sec->sacrificial_lamb[res]))
		{
			sec->sacrificial_lamb[res] = ' ';
		}
	}
	sec->sacrificial_lamb[511] = '\0';

	syslog(LOG_DEBUG, "The contents of the lamb are %s", sec->sacrificial_lamb);
#endif

	if (!sec->enable_mysql_auth) {
		APACHELOG(APLOG_DEBUG, r,
			"Not running mod-auth-mysql for %s - disabled", r->unparsed_uri);
		return DECLINED;
	}


	if (!auth_db_name && !sec->db_name) {
		APACHELOG(APLOG_ERR, r,
			"Failed to run mod-auth-mysql for %s: No database name specified", r->unparsed_uri);
		return DECLINED;
	}


	if ((res = ap_get_basic_auth_pw(r, &sent_pw))) {
		return res;
	}

#ifdef APACHE2
	APACHELOG(APLOG_DEBUG, r,
		"Starting basic user auth for [%s] in %s, child pid %i",
		r->user,
		sec->dir, getpid());
#else
	APACHELOG(APLOG_DEBUG, r,
		"Starting basic user auth for [%s] in %s, child pid %i",
		c->user,
		sec->dir, getpid());
#endif

#ifdef APACHE2
	switch (mysql_check_user_password(r, r->user, sent_pw, sec)) {
#else
	switch (mysql_check_user_password(r, c->user, sent_pw, sec)) {
#endif
		case 0:
			ap_note_basic_auth_failure(r);
			return HTTP_UNAUTHORIZED;
			break;
		case 1:
			return OK;
			break;
		case -1:
		default:
			APACHELOG(APLOG_DEBUG, r,
				"mysql_check_user_password returned error");
			return HTTP_INTERNAL_SERVER_ERROR;
			break;
	}
}
