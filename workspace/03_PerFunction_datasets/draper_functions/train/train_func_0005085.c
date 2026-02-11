zend_std_read_dimension(zval *object, zval *offset, int type TSRMLS_DC)
{
	zend_class_entry *ce = Z_OBJCE_P(object);
	zval *retval;

	if (EXPECTED(instanceof_function_ex(ce, zend_ce_arrayaccess, 1 TSRMLS_CC) != 0)) {
		if(offset == NULL) {

			ALLOC_INIT_ZVAL(offset);
		} else {
			SEPARATE_ARG_IF_REF(offset);
		}
		zend_call_method_with_1_params(&object, ce, NULL, "offsetget", &retval, offset);

		zval_ptr_dtor(&offset);

		if (UNEXPECTED(!retval)) {
			if (UNEXPECTED(!EG(exception))) {
				zend_error_noreturn(E_ERROR, "Undefined offset for object of type %s used as array", ce->name);
			}
			return 0;
		}


		Z_DELREF_P(retval);

		return retval;
	} else {
		zend_error_noreturn(E_ERROR, "Cannot use object of type %s as array", ce->name);
		return 0;
	}
}
