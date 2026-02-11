zend_std_call_getter(zval *object, zval *member TSRMLS_DC)
{
	zval *retval = NULL;
	zend_class_entry *ce = Z_OBJCE_P(object);


	SEPARATE_ARG_IF_REF(member);

	zend_call_method_with_1_params(&object, ce, &ce->__get, ZEND_GET_FUNC_NAME, &retval, member);

	zval_ptr_dtor(&member);

	if (retval) {
		Z_DELREF_P(retval);
	}

	return retval;
}
