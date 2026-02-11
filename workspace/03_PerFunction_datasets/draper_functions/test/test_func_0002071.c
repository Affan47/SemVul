dbh_method_get(
#if PHP_API_VERSION >= 20041225
	zval **object_pp,
#else
	zval *object,
#endif
	char *method_name, int method_len, const zend_literal *key TSRMLS_DC)
{
	zend_function *fbc = NULL;
	char *lc_method_name;
#if PHP_API_VERSION >= 20041225
	zval *object = *object_pp;
#endif
	pdo_dbh_t *dbh = zend_object_store_get_object(object TSRMLS_CC);

	lc_method_name = emalloc(method_len + 1);
	zend_str_tolower_copy(lc_method_name, method_name, method_len);

	if ((fbc = std_object_handlers.get_method(object_pp, method_name, method_len, key TSRMLS_CC)) == NULL) {


		if (!dbh->cls_methods[PDO_DBH_DRIVER_METHOD_KIND_DBH]) {
			if (!pdo_hash_methods(dbh,
				PDO_DBH_DRIVER_METHOD_KIND_DBH TSRMLS_CC)
				|| !dbh->cls_methods[PDO_DBH_DRIVER_METHOD_KIND_DBH]) {
				goto out;
			}
		}

		if (zend_hash_find(dbh->cls_methods[PDO_DBH_DRIVER_METHOD_KIND_DBH],
				lc_method_name, method_len+1, (void**)&fbc) == FAILURE) {
			if (!fbc) {
				fbc = NULL;
			}
		}
	}

out:
	efree(lc_method_name);
	return fbc;
}
