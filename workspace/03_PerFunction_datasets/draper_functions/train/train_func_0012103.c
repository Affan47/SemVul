spl_fixedarray_object_has_dimension(zval *object, zval *offset, int check_empty TSRMLS_DC)
{
	spl_fixedarray_object *intern;

	intern = (spl_fixedarray_object *)zend_object_store_get_object(object TSRMLS_CC);

	if (intern->fptr_offset_get) {
		zval *rv;
		SEPARATE_ARG_IF_REF(offset);
		zend_call_method_with_1_params(&object, intern->std.ce, &intern->fptr_offset_has, "offsetExists", &rv, offset);
		zval_ptr_dtor(&offset);
		if (rv) {
			zval_ptr_dtor(&intern->retval);
			MAKE_STD_ZVAL(intern->retval);
			ZVAL_ZVAL(intern->retval, rv, 1, 1);
			return zend_is_true(intern->retval);
		}
		return 0;
	}

	return spl_fixedarray_object_has_dimension_helper(intern, offset, check_empty TSRMLS_CC);
}
