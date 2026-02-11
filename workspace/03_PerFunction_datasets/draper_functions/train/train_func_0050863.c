is_identical_function(zval *result, zval *op1, zval *op2 TSRMLS_DC)
{
	Z_TYPE_P(result) = IS_BOOL;
	if (Z_TYPE_P(op1) != Z_TYPE_P(op2)) {
		Z_LVAL_P(result) = 0;
		return SUCCESS;
	}
	switch (Z_TYPE_P(op1)) {
		case IS_NULL:
			Z_LVAL_P(result) = 1;
			break;
		case IS_BOOL:
		case IS_LONG:
		case IS_RESOURCE:
			Z_LVAL_P(result) = (Z_LVAL_P(op1) == Z_LVAL_P(op2));
			break;
		case IS_DOUBLE:
			Z_LVAL_P(result) = (Z_DVAL_P(op1) == Z_DVAL_P(op2));
			break;
		case IS_STRING:
			Z_LVAL_P(result) = ((Z_STRLEN_P(op1) == Z_STRLEN_P(op2))
				&& (!memcmp(Z_STRVAL_P(op1), Z_STRVAL_P(op2), Z_STRLEN_P(op1))));
			break;
		case IS_ARRAY:
			Z_LVAL_P(result) = (Z_ARRVAL_P(op1) == Z_ARRVAL_P(op2) ||
				zend_hash_compare(Z_ARRVAL_P(op1), Z_ARRVAL_P(op2), (compare_func_t) hash_zval_identical_function, 1 TSRMLS_CC)==0);
			break;
		case IS_OBJECT:
			if (Z_OBJ_HT_P(op1) == Z_OBJ_HT_P(op2)) {
				Z_LVAL_P(result) = (Z_OBJ_HANDLE_P(op1) == Z_OBJ_HANDLE_P(op2));
			} else {
				Z_LVAL_P(result) = 0;
			}
			break;
		default:
			Z_LVAL_P(result) = 0;
			return FAILURE;
	}
	return SUCCESS;
}
