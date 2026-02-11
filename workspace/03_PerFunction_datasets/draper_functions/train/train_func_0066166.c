rinoo_http_response_setdefaultheaders(t_http *http)
{
	char tmp[24];

	if (rinoo_http_header_get(&http->response.headers, "Content-Length") == NULL) {
		if (snprintf(tmp, 24, "%lu", http->response.content_length) > 0) {
			rinoo_http_header_set(&http->response.headers, "Content-Length", tmp);
		}
	}
	if (rinoo_http_header_get(&http->response.headers, "Server") == NULL) {
		rinoo_http_header_set(&http->response.headers, "Server", RINOO_HTTP_SIGNATURE);
	}
}
