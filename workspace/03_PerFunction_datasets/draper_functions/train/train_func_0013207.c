pdo_sqlite2_stmt_execute(pdo_stmt_t *stmt TSRMLS_DC)
{
	pdo_sqlite2_stmt *S = (pdo_sqlite2_stmt*)stmt->driver_data;
	char *errmsg = NULL;
	const char *tail;

	if (stmt->executed && !S->done) {
		sqlite_finalize(S->vm, &errmsg);
		pdo_sqlite2_error_stmt(errmsg, stmt);
		errmsg = NULL;
		S->vm = NULL;
	}

	S->einfo.errcode = sqlite_compile(S->H->db, stmt->active_query_string, &tail, &S->vm, &errmsg);
	if (S->einfo.errcode != SQLITE_OK) {
		pdo_sqlite2_error_stmt(errmsg, stmt);
		return 0;
	}

	S->done = 0;
	S->einfo.errcode = sqlite_step(S->vm, &S->ncols, &S->rowdata, &S->colnames);
	switch (S->einfo.errcode) {
		case SQLITE_ROW:
			S->pre_fetched = 1;
			stmt->column_count = S->ncols;
			return 1;

		case SQLITE_DONE:
			stmt->column_count = S->ncols;
			stmt->row_count = sqlite_changes(S->H->db);
			S->einfo.errcode = sqlite_reset(S->vm, &errmsg);
			if (S->einfo.errcode != SQLITE_OK) {
				pdo_sqlite2_error_stmt(errmsg, stmt);
			}
			S->done = 1;
			return 1;

		case SQLITE_ERROR:
		case SQLITE_MISUSE:
		case SQLITE_BUSY:
		default:
			pdo_sqlite2_error_stmt(errmsg, stmt);
			return 0;
	}
}
