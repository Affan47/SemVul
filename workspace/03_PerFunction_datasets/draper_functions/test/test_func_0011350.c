concat_function(zval *result, zval *op1, zval *op2 TSRMLS_DC)
{
	zval op1_copy, op2_copy;
	int use_copy1 = 0, use_copy2 = 0;

	if (Z_TYPE_P(op1) != IS_STRING) {
		zend_make_printable_zval(op1, &op1_copy, &use_copy1);
	}
	if (Z_TYPE_P(op2) != IS_STRING) {
		zend_make_printable_zval(op2, &op2_copy, &use_copy2);
	}

	if (use_copy1) {


		if (result == op1) {
			zval_dtor(op1);
		}
		op1 = &op1_copy;
	}
	if (use_copy2) {
		op2 = &op2_copy;
	}
	if (result==op1) {
		uint res_len = Z_STRLEN_P(op1) + Z_STRLEN_P(op2);

		if (Z_STRLEN_P(result) < 0 || (int) (Z_STRLEN_P(op1) + Z_STRLEN_P(op2)) < 0) {
			efree(Z_STRVAL_P(result));
			ZVAL_EMPTY_STRING(result);
			zend_error(E_ERROR, "String size overflow");
		}

		Z_STRVAL_P(result) = erealloc(Z_STRVAL_P(result), res_len+1);

		memcpy(Z_STRVAL_P(result)+Z_STRLEN_P(result), Z_STRVAL_P(op2), Z_STRLEN_P(op2));
		Z_STRVAL_P(result)[res_len]=0;
		Z_STRLEN_P(result) = res_len;
	} else {
		Z_STRLEN_P(result) = Z_STRLEN_P(op1) + Z_STRLEN_P(op2);
		Z_STRVAL_P(result) = (char *) emalloc(Z_STRLEN_P(result) + 1);
		memcpy(Z_STRVAL_P(result), Z_STRVAL_P(op1), Z_STRLEN_P(op1));
		memcpy(Z_STRVAL_P(result)+Z_STRLEN_P(op1), Z_STRVAL_P(op2), Z_STRLEN_P(op2));
		Z_STRVAL_P(result)[Z_STRLEN_P(result)] = 0;
		Z_TYPE_P(result) = IS_STRING;
	}
	if (use_copy1) {
		zval_dtor(op1);
	}
	if (use_copy2) {
		zval_dtor(op2);
	}
	return SUCCESS;
}
