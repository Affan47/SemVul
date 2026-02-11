sapi_cli_server_send_headers(sapi_headers_struct *sapi_headers TSRMLS_DC)
{
	php_cli_server_client *client = SG(server_context);
	smart_str buffer = { 0 };
	sapi_header_struct *h;
	zend_llist_position pos;

	if (client == NULL || SG(request_info).no_headers) {
		return SAPI_HEADER_SENT_SUCCESSFULLY;
	}

	if (SG(sapi_headers).http_status_line) {
		smart_str_appends(&buffer, SG(sapi_headers).http_status_line);
		smart_str_appendl(&buffer, "\r\n", 2);
	} else {
		append_http_status_line(&buffer, client->request.protocol_version, SG(sapi_headers).http_response_code, 0);
	}

	append_essential_headers(&buffer, client, 0);

	h = (sapi_header_struct*)zend_llist_get_first_ex(&sapi_headers->headers, &pos);
	while (h) {
		if (!h->header_len) {
			continue;
		}
		smart_str_appendl(&buffer, h->header, h->header_len);
		smart_str_appendl(&buffer, "\r\n", 2);
		h = (sapi_header_struct*)zend_llist_get_next_ex(&sapi_headers->headers, &pos);
	}
	smart_str_appendl(&buffer, "\r\n", 2);

	php_cli_server_client_send_through(client, buffer.c, buffer.len);

	smart_str_free(&buffer);
	return SAPI_HEADER_SENT_SUCCESSFULLY;
}
