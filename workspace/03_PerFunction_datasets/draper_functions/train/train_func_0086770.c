sapi_cli_server_read_cookies(TSRMLS_D)
{
	php_cli_server_client *client = SG(server_context);
	char **val;
	if (FAILURE == zend_hash_find(&client->request.headers, "Cookie", sizeof("Cookie"), (void**)&val)) {
		return NULL;
	}
	return *val;
}
