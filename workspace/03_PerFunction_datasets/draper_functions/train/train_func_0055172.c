php_array_element_dump(zval **zv TSRMLS_DC, int num_args, va_list args, zend_hash_key *hash_key)
{
	int level;

	level = va_arg(args, int);

	if (hash_key->nKeyLength == 0) {
		php_printf("%*c[%ld]=>\n", level + 1, ' ', hash_key->h);
	} else {
		php_printf("%*c[\"", level + 1, ' ');
		PHPWRITE(hash_key->arKey, hash_key->nKeyLength - 1);
		php_printf("\"]=>\n");
	}
	php_var_dump(zv, level + 2 TSRMLS_CC);
	return 0;
}
