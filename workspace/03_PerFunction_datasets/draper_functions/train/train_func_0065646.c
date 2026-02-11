pdo_sqlite2_fetch_error_func(pdo_dbh_t *dbh, pdo_stmt_t *stmt, zval *info TSRMLS_DC)
{
	pdo_sqlite2_db_handle *H = (pdo_sqlite2_db_handle *)dbh->driver_data;
	pdo_sqlite2_error_info *einfo = &H->einfo;
	pdo_sqlite2_stmt *S;

	if (stmt) {
		S = stmt->driver_data;
		einfo = &S->einfo;
	}

	if (einfo->errcode) {
		add_next_index_long(info, einfo->errcode);
		if (einfo->errmsg) {
			add_next_index_string(info, einfo->errmsg, 1);
		}
	}

	return 1;
}
