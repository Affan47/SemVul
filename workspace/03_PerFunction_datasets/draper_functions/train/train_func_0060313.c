http_request(session *s, void *param)
{
	const char *filename = session_get_stash(s, HTTP_RESOURCE);
	char body[1024];
	const size_t len =
		sprintf(body,
		"<html>\n<title>404 NOT FOUND</title>\n<body>\n<h1>404 NOT FOUND: '%s'</h1>\n</body>\n</html>\n",
		filename
		);

	httpserver_response(s, 404, "NOT FOUND", len, "text/html");
	if (g_http_debug) printf("HTTP: %s", body);
	return session_write(s, body, len);
}
