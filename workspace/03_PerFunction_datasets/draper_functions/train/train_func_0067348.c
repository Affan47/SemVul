dbh_free(pdo_dbh_t *dbh TSRMLS_DC)
{
	int i;

	if (--dbh->refcount)
		return;

	if (dbh->query_stmt) {
		zval_dtor(&dbh->query_stmt_zval);
		dbh->query_stmt = NULL;
	}

	if (dbh->methods) {
		dbh->methods->closer(dbh TSRMLS_CC);
	}

	if (dbh->data_source) {
		pefree((char *)dbh->data_source, dbh->is_persistent);
	}
	if (dbh->username) {
		pefree(dbh->username, dbh->is_persistent);
	}
	if (dbh->password) {
		pefree(dbh->password, dbh->is_persistent);
	}

	if (dbh->persistent_id) {
		pefree((char *)dbh->persistent_id, dbh->is_persistent);
	}

	if (dbh->def_stmt_ctor_args) {
		zval_ptr_dtor(&dbh->def_stmt_ctor_args);
	}

	for (i = 0; i < PDO_DBH_DRIVER_METHOD_KIND__MAX; i++) {
		if (dbh->cls_methods[i]) {
			zend_hash_destroy(dbh->cls_methods[i]);
			pefree(dbh->cls_methods[i], dbh->is_persistent);
		}
	}

	pefree(dbh, dbh->is_persistent);
}
