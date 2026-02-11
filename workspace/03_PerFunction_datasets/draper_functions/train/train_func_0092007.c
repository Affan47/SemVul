mysql_cursor_statement_detect (GSQLCursor *cursor)
{
	GSQL_TRACE_FUNC;

	gchar *stmt_char;
	gdouble affect = 0;
	GSQLEMySQLCursor  *e_cursor = NULL;


	e_cursor = cursor->spec;

	affect = mysql_stmt_affected_rows(e_cursor->statement);

	stmt_char = g_ascii_strdown (cursor->sql, 10);

	switch (0)
	{
		case 0:
			if (g_str_has_prefix (stmt_char, "select"))
			{
				GSQL_DEBUG ("'select' statement");
				cursor->stmt_type = GSQL_CURSOR_STMT_SELECT;
				break;
			}

			if (g_str_has_prefix (stmt_char, "show"))
			{
				GSQL_DEBUG ("'show' statement");
				cursor->stmt_type = GSQL_CURSOR_STMT_SELECT;
				break;
			}

			if (g_str_has_prefix (stmt_char, "desc"))
			{
				GSQL_DEBUG ("'desc' statement");
				cursor->stmt_type = GSQL_CURSOR_STMT_SELECT;
				break;
			}

			if (g_str_has_prefix (stmt_char, "insert"))
			{
				GSQL_DEBUG ("'insert' statement");
				cursor->stmt_type = GSQL_CURSOR_STMT_INSERT;
				cursor->stmt_affected_rows = affect;
				break;
			}

			if (g_str_has_prefix (stmt_char, "update"))
			{
				GSQL_DEBUG ("'update' statement");
				cursor->stmt_type = GSQL_CURSOR_STMT_UPDATE;
				cursor->stmt_affected_rows = affect;
				break;
			}

			if (g_str_has_prefix (stmt_char, "delete"))
			{
				GSQL_DEBUG ("'delete' statement");
				cursor->stmt_type = GSQL_CURSOR_STMT_DELETE;
				cursor->stmt_affected_rows = affect;
				break;
			}

			if (g_str_has_prefix (stmt_char, "create"))
			{
				GSQL_DEBUG ("'create' statement");
				cursor->stmt_type = GSQL_CURSOR_STMT_CREATE;
				break;
			}

			if (g_str_has_prefix (stmt_char, "drop"))
			{
				GSQL_DEBUG ("'drop' statement");
				cursor->stmt_type = GSQL_CURSOR_STMT_DROP;
				break;
			}

			if (g_str_has_prefix (stmt_char, "alter"))
			{
				GSQL_DEBUG ("'alter' statement");
				cursor->stmt_type = GSQL_CURSOR_STMT_ALTER;
				break;
			}

		default:
				GSQL_DEBUG ("default 'exec' statement");
				cursor->stmt_type = GSQL_CURSOR_STMT_EXEC;
	}


}
