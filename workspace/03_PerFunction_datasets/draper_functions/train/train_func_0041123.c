zend_traits_method_compatibility_check(zend_function *fn, zend_function *other_fn TSRMLS_DC)
{
	zend_uint    fn_flags = fn->common.scope->ce_flags;
	zend_uint other_flags = other_fn->common.scope->ce_flags;

	return zend_do_perform_implementation_check(fn, other_fn TSRMLS_CC)
		&& ((other_fn->common.scope->ce_flags & ZEND_ACC_INTERFACE) || zend_do_perform_implementation_check(other_fn, fn TSRMLS_CC))
		&& ((fn_flags & (ZEND_ACC_FINAL|ZEND_ACC_STATIC)) ==
		    (other_flags & (ZEND_ACC_FINAL|ZEND_ACC_STATIC)));
}
