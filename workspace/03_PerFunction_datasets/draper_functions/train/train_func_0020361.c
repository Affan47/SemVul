uridecode(struct ast_channel *chan, const char *cmd, char *data,
		     char *buf, size_t len)
{
	if (ast_strlen_zero(data)) {
		ast_log(LOG_WARNING, "Syntax: URIDECODE(<data>) - missing argument!\n");
		return -1;
	}

	ast_copy_string(buf, data, len);
	ast_uri_decode(buf, ast_uri_http);

	return 0;
}
