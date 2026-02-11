php_handle_special_queries(TSRMLS_D)
{
	if (PG(expose_php) && SG(request_info).query_string && SG(request_info).query_string[0] == '=') {
		if (php_info_logos(SG(request_info).query_string + 1 TSRMLS_CC)) {
			return 1;
		} else if (!strcmp(SG(request_info).query_string + 1, PHP_CREDITS_GUID)) {
			php_print_credits(PHP_CREDITS_ALL TSRMLS_CC);
			return 1;
		}
	}
	return 0;
}
