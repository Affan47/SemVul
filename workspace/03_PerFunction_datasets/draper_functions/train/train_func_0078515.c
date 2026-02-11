php_sqlite3_stmt_object_free_storage(void *object TSRMLS_DC)
{
	php_sqlite3_stmt *intern = (php_sqlite3_stmt *)object;

	if (!intern) {
		return;
	}

	if (intern->bound_params) {
		zend_hash_destroy(intern->bound_params);
		FREE_HASHTABLE(intern->bound_params);
		intern->bound_params = NULL;
	}

	if (intern->initialised) {
		zend_llist_del_element(&(intern->db_obj->free_list), intern->stmt,
			(int (*)(void *, void *)) php_sqlite3_compare_stmt_free);
	}

	if (intern->db_obj_zval) {
		Z_DELREF_P(intern->db_obj_zval);
	}

	zend_object_std_dtor(&intern->zo TSRMLS_CC);
	efree(intern);
}
