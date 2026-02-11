pdo_sqlite2_stmt_fetch(pdo_stmt_t *stmt,
	enum pdo_fetch_orientation ori, long offset TSRMLS_DC)
{
	pdo_sqlite2_stmt *S = (pdo_sqlite2_stmt*)stmt->driver_data;
	char *errmsg = NULL;

	if (!S->vm) {
		return 0;
	}
	if (S->pre_fetched) {
		S->pre_fetched = 0;
		return 1;
	}
	if (S->done) {
		return 0;
	}

	S->einfo.errcode = sqlite_step(S->vm, &S->ncols, &S->rowdata, &S->colnames);
	switch (S->einfo.errcode) {
		case SQLITE_ROW:
			return 1;

		case SQLITE_DONE:
			S->done = 1;
			S->einfo.errcode = sqlite_reset(S->vm, &errmsg);
			if (S->einfo.errcode != SQLITE_OK) {
				pdo_sqlite2_error_stmt(errmsg, stmt);
				errmsg = NULL;
			}
			return 0;

		default:
			pdo_sqlite2_error_stmt(errmsg, stmt);
			return 0;
	}
}
