zend_insert_literal(zend_op_array *op_array, const zval *zv, int literal_position TSRMLS_DC)
{
	if (Z_TYPE_P(zv) == IS_STRING || Z_TYPE_P(zv) == IS_CONSTANT) {
		zval *z = (zval*)zv;
		Z_STRVAL_P(z) = (char*)zend_new_interned_string(Z_STRVAL_P(zv), Z_STRLEN_P(zv) + 1, 1 TSRMLS_CC);
	}
	CONSTANT_EX(op_array, literal_position) = *zv;
	Z_SET_REFCOUNT(CONSTANT_EX(op_array, literal_position), 2);
	Z_SET_ISREF(CONSTANT_EX(op_array, literal_position));
	op_array->literals[literal_position].hash_value = 0;
	op_array->literals[literal_position].cache_slot = -1;
}
