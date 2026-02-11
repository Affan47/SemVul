user_fetch(dynalogin_user_data_t **ud, const dynalogin_userid_t userid,
		apr_pool_t *pool)
{
	dynalogin_user_data_t *_ud = NULL;
	odbc_connection_t *c;
	SQLRETURN ret;
	SQLLEN indicator;
	int field;
	char *scheme_name;

	char *_dsn = DB_DSN;

	*ud = NULL;

	if(odbc_build_connection(&c, pool) != APR_SUCCESS)
		return;


	if(odbc_set_string(userid, c->query_stmt, 1, &indicator) != APR_SUCCESS)
	{
		odbc_error_cleanup("SQLBindParameter", c);
		return;
	}

	if(!SQL_SUCCEEDED(ret = SQLExecute(c->query_stmt)))
	{

		odbc_error_cleanup("SQLExecute", c);
		return;
	}

	if(SQL_SUCCEEDED(ret = SQLFetch(c->query_stmt))) {
		if((_ud = apr_pcalloc(pool, sizeof(dynalogin_user_data_t))) != NULL)
		{
			field = 2;
			odbc_get_string(&(_ud->userid), c->query_stmt, field++, pool);
			odbc_get_string(&(scheme_name), c->query_stmt, field++, pool);
			_ud->scheme = get_scheme_by_name(scheme_name);
			odbc_get_string(&(_ud->secret), c->query_stmt, field++, pool);
			odbc_get_uint64(&(_ud->counter), c->query_stmt, field++, &indicator);
			odbc_get_int(&(_ud->failure_count), c->query_stmt, field++, &indicator);
			odbc_get_int(&(_ud->locked), c->query_stmt, field++, &indicator);
			odbc_get_datetime(&(_ud->last_success), c->query_stmt, field++, &indicator);
			odbc_get_datetime(&(_ud->last_attempt), c->query_stmt, field++, &indicator);
			odbc_get_string(&(_ud->last_code), c->query_stmt, field++, pool);
			odbc_get_string(&(_ud->password), c->query_stmt, field++, pool);

			syslog(LOG_DEBUG, "got user %s count %ju", _ud->userid, _ud->counter);
		}
		else
		{
			syslog(LOG_ERR, "apr_pcalloc failed");
			odbc_cleanup(c);
			return ;
		}
	} else if(ret == SQL_NO_DATA) {
		syslog(LOG_INFO, "no row found for user: ", userid);
		odbc_cleanup(c);
		return;
	} else {
		odbc_error_cleanup("SQLFetch", c);
		return;
	}

	odbc_cleanup(c);

	*ud = _ud;

	syslog(LOG_DEBUG, "user = %s, count = %ju", userid, _ud->counter);
	return;
}
