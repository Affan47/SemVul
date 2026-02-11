evhttp_parse_response_line(struct evhttp_request *req, char *line)
{
	char *protocol;
	char *number;
	const char *readable = "";

	protocol = strsep(&line, " ");
	if (line == NULL)
		return (-1);
	number = strsep(&line, " ");
	if (line != NULL)
		readable = line;

	if (evhttp_parse_http_version(protocol, req) < 0)
		return (-1);

	req->response_code = atoi(number);
	if (!evhttp_valid_response_code(req->response_code)) {
		event_debug(("%s: bad response code \"%s\"",
			__func__, number));
		return (-1);
	}

	if ((req->response_code_line = mm_strdup(readable)) == NULL) {
		event_warn("%s: strdup", __func__);
		return (-1);
	}

	return (0);
}
