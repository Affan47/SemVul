spl_fixedarray_object_write_dimension_helper(spl_fixedarray_object *intern, zval *offset, zval *value TSRMLS_DC)
{
	long index;

	if (!offset) {

		zend_throw_exception(spl_ce_RuntimeException, "Index invalid or out of range", 0 TSRMLS_CC);
		return;
	}

	if (Z_TYPE_P(offset) != IS_LONG) {
		index = spl_offset_convert_to_long(offset TSRMLS_CC);
	} else {
		index = Z_LVAL_P(offset);
	}

	if (index < 0 || intern->array == NULL || index >= intern->array->size) {
		zend_throw_exception(spl_ce_RuntimeException, "Index invalid or out of range", 0 TSRMLS_CC);
		return;
	} else {
		if (intern->array->elements[index]) {
			zval_ptr_dtor(&(intern->array->elements[index]));
		}
		SEPARATE_ARG_IF_REF(value);
		intern->array->elements[index] = value;
	}
}
