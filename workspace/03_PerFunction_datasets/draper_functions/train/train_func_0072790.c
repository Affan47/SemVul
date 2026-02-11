shift_left_function(zval *result, zval *op1, zval *op2 TSRMLS_DC)
{
	zval op1_copy, op2_copy;
	long op1_lval;

	zendi_convert_to_long(op1, op1_copy, result);
	op1_lval = Z_LVAL_P(op1);
	zendi_convert_to_long(op2, op2_copy, result);
	ZVAL_LONG(result, op1_lval << Z_LVAL_P(op2));
	return SUCCESS;
}
