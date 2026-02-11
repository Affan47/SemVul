add_get_assoc_string_ex(zval *arg, const char *key, uint key_len, const char *str, void **dest, int duplicate)
{
	zval *tmp;

	MAKE_STD_ZVAL(tmp);
	ZVAL_STRING(tmp, str, duplicate);

	return zend_symtable_update(Z_ARRVAL_P(arg), key, key_len, (void *) &tmp, sizeof(zval *), dest);
}
