method_from_string(enum http_method *m, const char *method)
{
	if (!evutil_ascii_strcasecmp(method, "GET"))
		*m = METH_GET;
	else if (!evutil_ascii_strcasecmp(method, "HEAD"))
		*m = METH_HEAD;
	else if (!evutil_ascii_strcasecmp(method, "POST"))
		*m = METH_POST;
	else if (!evutil_ascii_strcasecmp(method, "PUT"))
		*m = METH_PUT;
	else if (!evutil_ascii_strcasecmp(method, "CONNECT"))
		*m = METH_CONNECT;
	else {
		log_warn("method_from_string: unknown method, '%s'", method);
		return -1;
	}

	return 0;
}
