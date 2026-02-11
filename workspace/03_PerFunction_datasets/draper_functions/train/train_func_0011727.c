php_natsort(INTERNAL_FUNCTION_PARAMETERS, int fold_case)
{
	zval *array;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &array) == FAILURE) {
		return;
	}

	if (fold_case) {
		if (zend_hash_sort(Z_ARRVAL_P(array), zend_qsort, php_array_natural_case_compare, 0 TSRMLS_CC) == FAILURE) {
			return;
		}
	} else {
		if (zend_hash_sort(Z_ARRVAL_P(array), zend_qsort, php_array_natural_compare, 0 TSRMLS_CC) == FAILURE) {
			return;
		}
	}

	RETURN_TRUE;
}
