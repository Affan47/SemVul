pgsql_cursor_open (GSQLCursor *cursor) {
	GSQL_TRACE_FUNC;
	PGconn *pgconn;
	GSQLEPGSQLSession *e_session = NULL;
	GSQLEPGSQLCursor  *e_cursor = NULL;
	GSQLEPGSQLVariable *e_var;
	GSQLVariable *var;
	GSQLWorkspace *workspace = NULL;
	PGSQL_FIELD *field;
	gulong n, n_fields, is_null = 1;
	gchar error_str[2048];

	g_return_val_if_fail (GSQL_IS_CURSOR(cursor), GSQL_CURSOR_STATE_ERROR);
	g_return_val_if_fail (GSQL_IS_SESSION(cursor->session),
	                      GSQL_CURSOR_STATE_ERROR);
	e_session = cursor->session->spec;

	workspace = gsql_session_get_workspace (cursor->session);
	g_return_val_if_fail(GSQL_IS_WORKSPACE(workspace),
	                     GSQL_CURSOR_STATE_ERROR);

	pgconn = e_session->pgconn;

	if (!pgsql_cursor_prepare (cursor)) {
		return GSQL_CURSOR_STATE_ERROR;
	}

	e_cursor = cursor->spec;
	e_cursor->result = PQexec(e_session->pgconn, cursor->sql);

	if ( ! e_cursor->result ) {
		g_sprintf ( error_str, "Error occured: %s",
			    pgsql_session_get_error(cursor->session) );
		gsql_message_add (workspace, GSQL_MESSAGE_ERROR, error_str);

		return GSQL_CURSOR_STATE_ERROR;
	}

	pgsql_cursor_statement_detect (cursor);

	n_fields =  PQnfields (e_cursor->result);
	if (n_fields == 0 &&
	    PQresultStatus(e_cursor->result) == PGRES_COMMAND_OK)
		return GSQL_CURSOR_STATE_OPEN;

	if (n_fields == 0 &&
	    PQresultStatus(e_cursor->result) != PGRES_COMMAND_OK) {
		g_sprintf ( error_str, "Error occured: %s",
			    pgsql_session_get_error(cursor->session) );
		gsql_message_add (workspace, GSQL_MESSAGE_ERROR, error_str);
		return GSQL_CURSOR_STATE_ERROR;
	}

	for (n = 0; n < n_fields; n++) {

		field = g_malloc0 ( sizeof(PGSQL_FIELD) );
		field->name = PQfname(e_cursor->result, n);
		field->type = PQftype(e_cursor->result, n);
		field->size = PQfsize(e_cursor->result, n);

		var = gsql_variable_new ();
		pgsql_variable_init (var, field);
		cursor->var_list = g_list_append (cursor->var_list, var);
	}

	return GSQL_CURSOR_STATE_OPEN;
}
