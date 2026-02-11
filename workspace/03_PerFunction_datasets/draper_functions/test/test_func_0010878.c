zend_make_printable_zval(zval *expr, zval *expr_copy, int *use_copy)
{
	if (Z_TYPE_P(expr)==IS_STRING) {
		*use_copy = 0;
		return;
	}
	switch (Z_TYPE_P(expr)) {
		case IS_NULL:
			Z_STRLEN_P(expr_copy) = 0;
			Z_STRVAL_P(expr_copy) = STR_EMPTY_ALLOC();
			break;
		case IS_BOOL:
			if (Z_LVAL_P(expr)) {
				Z_STRLEN_P(expr_copy) = 1;
				Z_STRVAL_P(expr_copy) = estrndup("1", 1);
			} else {
				Z_STRLEN_P(expr_copy) = 0;
				Z_STRVAL_P(expr_copy) = STR_EMPTY_ALLOC();
			}
			break;
		case IS_RESOURCE:
			Z_STRVAL_P(expr_copy) = (char *) emalloc(sizeof("Resource id #") - 1 + MAX_LENGTH_OF_LONG);
			Z_STRLEN_P(expr_copy) = snprintf(Z_STRVAL_P(expr_copy), sizeof("Resource id #") - 1 + MAX_LENGTH_OF_LONG, "Resource id #%ld", Z_LVAL_P(expr));
			break;
		case IS_ARRAY:
			zend_error(E_NOTICE, "Array to string conversion");
			Z_STRLEN_P(expr_copy) = sizeof("Array") - 1;
			Z_STRVAL_P(expr_copy) = estrndup("Array", Z_STRLEN_P(expr_copy));
			break;
		case IS_OBJECT:
			{
				TSRMLS_FETCH();

				if (zend_std_cast_object_tostring(expr, expr_copy, IS_STRING TSRMLS_CC) == SUCCESS) {
					break;
				}
				if (Z_OBJ_HANDLER_P(expr, cast_object)) {
					zval *val;

					ALLOC_ZVAL(val);
					INIT_PZVAL_COPY(val, expr);
					zval_copy_ctor(val);
					if (Z_OBJ_HANDLER_P(expr, cast_object)(val, expr_copy, IS_STRING TSRMLS_CC) == SUCCESS) {
						zval_ptr_dtor(&val);
						break;
					}
					zval_ptr_dtor(&val);
				}
				if (!Z_OBJ_HANDLER_P(expr, cast_object) && Z_OBJ_HANDLER_P(expr, get)) {
					zval *z = Z_OBJ_HANDLER_P(expr, get)(expr TSRMLS_CC);

					Z_ADDREF_P(z);
					if (Z_TYPE_P(z) != IS_OBJECT) {
						zend_make_printable_zval(z, expr_copy, use_copy);
						if (*use_copy) {
							zval_ptr_dtor(&z);
						} else {
							ZVAL_ZVAL(expr_copy, z, 0, 1);
							*use_copy = 1;
						}
						return;
					}
					zval_ptr_dtor(&z);
				}
				zend_error(EG(exception) ? E_ERROR : E_RECOVERABLE_ERROR, "Object of class %s could not be converted to string", Z_OBJCE_P(expr)->name);
				Z_STRLEN_P(expr_copy) = 0;
				Z_STRVAL_P(expr_copy) = STR_EMPTY_ALLOC();
			}
			break;
		case IS_DOUBLE:
			*expr_copy = *expr;
			zval_copy_ctor(expr_copy);
			zend_locale_sprintf_double(expr_copy ZEND_FILE_LINE_CC);
			break;
		default:
			*expr_copy = *expr;
			zval_copy_ctor(expr_copy);
			convert_to_string(expr_copy);
			break;
	}
	Z_TYPE_P(expr_copy) = IS_STRING;
	*use_copy = 1;
}
