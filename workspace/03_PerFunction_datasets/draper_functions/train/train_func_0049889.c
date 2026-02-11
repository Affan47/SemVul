spl_offset_convert_to_long(zval *offset TSRMLS_DC)
{
	switch (Z_TYPE_P(offset)) {
	case IS_STRING:
		ZEND_HANDLE_NUMERIC(Z_STRVAL_P(offset), Z_STRLEN_P(offset)+1, idx);
		break;
	case IS_DOUBLE:
		return (long)Z_DVAL_P(offset);
	case IS_RESOURCE:
	case IS_BOOL:
	case IS_LONG:
		return Z_LVAL_P(offset);
	}
	return -1;
}
