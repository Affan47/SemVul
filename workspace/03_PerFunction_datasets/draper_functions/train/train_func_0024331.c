zend_print_zval_ex(zend_write_func_t write_func, zval *expr, int indent)
{
	zval expr_copy;
	int use_copy;

	zend_make_printable_zval(expr, &expr_copy, &use_copy);
	if (use_copy) {
		expr = &expr_copy;
	}
	if (Z_STRLEN_P(expr) == 0) {
		if (use_copy) {
			zval_dtor(expr);
		}
		return 0;
	}
	write_func(Z_STRVAL_P(expr), Z_STRLEN_P(expr));
	if (use_copy) {
		zval_dtor(expr);
	}
	return Z_STRLEN_P(expr);
}
