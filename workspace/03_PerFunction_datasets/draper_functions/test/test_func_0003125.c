debug_backtrace_get_args(void **curpos TSRMLS_DC)
{
	void **p = curpos;
	zval *arg_array, **arg;
	int arg_count = (int)(zend_uintptr_t) *p;

	MAKE_STD_ZVAL(arg_array);
	array_init_size(arg_array, arg_count);
	p -= arg_count;

	while (--arg_count >= 0) {
		arg = (zval **) p++;
		if (*arg) {
			if (Z_TYPE_PP(arg) != IS_OBJECT) {
				SEPARATE_ZVAL_TO_MAKE_IS_REF(arg);
			}
			Z_ADDREF_PP(arg);
			add_next_index_zval(arg_array, *arg);
		} else {
			add_next_index_null(arg_array);
		}
	}

	return arg_array;
}
