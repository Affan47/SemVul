php_prefix_varname(zval *result, zval *prefix, char *var_name, int var_name_len, zend_bool add_underscore TSRMLS_DC)
{
	Z_STRLEN_P(result) = Z_STRLEN_P(prefix) + (add_underscore ? 1 : 0) + var_name_len;
	Z_TYPE_P(result) = IS_STRING;
	Z_STRVAL_P(result) = emalloc(Z_STRLEN_P(result) + 1);
	memcpy(Z_STRVAL_P(result), Z_STRVAL_P(prefix), Z_STRLEN_P(prefix));

	if (add_underscore) {
		Z_STRVAL_P(result)[Z_STRLEN_P(prefix)] = '_';
	}

	memcpy(Z_STRVAL_P(result) + Z_STRLEN_P(prefix) + (add_underscore ? 1 : 0), var_name, var_name_len + 1);

	return SUCCESS;
}
