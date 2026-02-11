get_pg_pw(request_rec * r, const char *user, pg_auth_config_rec * sec)
{
	char query[MAX_STRING_LEN];
	char *safe_user;
	int n;

	safe_user = apr_palloc(r->pool, 1 + 2 * strlen(user));
	pg_check_string(safe_user, user, strlen(user), r, sec);

#ifdef DEBUG_AUTH_PGSQL
	ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
				  "[mod_auth_pgsql.c] - get_pg_pw - going to retrieve password for user \"%s\" from database",
				  user);
#endif

	if ((!sec->auth_pg_pwd_table) ||
		(!sec->auth_pg_pwd_field) || (!sec->auth_pg_uname_field)) {
		apr_snprintf(pg_errstr, MAX_STRING_LEN,
					 "PG: Missing parameters for password lookup: %s%s%s",
					 (sec->auth_pg_pwd_table ? "" : "Password table "),
					 (sec->
					  auth_pg_pwd_field ? "" : "Password field name "),
					 (sec->
					  auth_pg_uname_field ? "" : "UserID field name "));
		return NULL;
	};

	if (sec->auth_pg_lowercaseuid) {

		n = 0;
		while (safe_user[n] && n < (MAX_STRING_LEN - 1)) {
			if (isupper(safe_user[n])) {
				safe_user[n] = tolower(safe_user[n]);
			}
			n++;
		}
	}

	if (sec->auth_pg_uppercaseuid) {

		n = 0;
		while (safe_user[n] && n < (MAX_STRING_LEN - 1)) {
			if (islower(safe_user[n])) {
				safe_user[n] = toupper(safe_user[n]);
			}
			n++;
		}
	}

	n = apr_snprintf(query, MAX_STRING_LEN,
					 "select %s from %s where %s='%s' %s",
					 sec->auth_pg_pwd_field, sec->auth_pg_pwd_table,
					 sec->auth_pg_uname_field, safe_user,
					 sec->auth_pg_pwd_whereclause ? sec->
					 auth_pg_pwd_whereclause : "");

	if (n < 0 || n > MAX_STRING_LEN) {
		apr_snprintf(pg_errstr, MAX_STRING_LEN,
					 "PG: Detected SQL-truncation attack. Auth aborted.");
		return NULL;
	}
	return do_pg_query(r, query, sec);
}
