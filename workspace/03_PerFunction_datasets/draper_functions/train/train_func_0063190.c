row_get_properties(zval *object TSRMLS_DC)
{
	pdo_stmt_t * stmt = (pdo_stmt_t *) zend_object_store_get_object(object TSRMLS_CC);
	int i;

	if (stmt == NULL) {
		return NULL;
	}

	for (i = 0; i < stmt->column_count; i++) {
		zval *val;
		MAKE_STD_ZVAL(val);
		fetch_value(stmt, val, i, NULL TSRMLS_CC);

		zend_hash_update(stmt->properties, stmt->columns[i].name, stmt->columns[i].namelen + 1, (void *)&val, sizeof(zval *), NULL);
	}

	return stmt->properties;
}
