zend_add_ns_func_name_literal(zend_op_array *op_array, const zval *zv TSRMLS_DC)
{
	int ret;
	char *lc_name;
	const char *ns_separator;
	int lc_len;
	zval c;
	int lc_literal;

	if (op_array->last_literal > 0 &&
	    &op_array->literals[op_array->last_literal - 1].constant == zv &&
	    op_array->literals[op_array->last_literal - 1].cache_slot == -1) {

		ret = op_array->last_literal - 1;
	} else {
		ret = zend_add_literal(op_array, zv TSRMLS_CC);
	}

	lc_name = zend_str_tolower_dup(Z_STRVAL_P(zv), Z_STRLEN_P(zv));
	ZVAL_STRINGL(&c, lc_name, Z_STRLEN_P(zv), 0);
	lc_literal = zend_add_literal(CG(active_op_array), &c TSRMLS_CC);
	CALCULATE_LITERAL_HASH(lc_literal);

	ns_separator = (const char*)zend_memrchr(Z_STRVAL_P(zv), '\\', Z_STRLEN_P(zv)) + 1;
	lc_len = Z_STRLEN_P(zv) - (ns_separator - Z_STRVAL_P(zv));
	lc_name = zend_str_tolower_dup(ns_separator, lc_len);
	ZVAL_STRINGL(&c, lc_name, lc_len, 0);
	lc_literal = zend_add_literal(CG(active_op_array), &c TSRMLS_CC);
	CALCULATE_LITERAL_HASH(lc_literal);

	return ret;
}
