send_eivr_event(FILE *handle, const char event, const char *data,
	const struct ast_channel *chan)
{
	struct ast_str *tmp = ast_str_create(12);

	ast_str_append(&tmp, 0, "%c,%10d", event, (int)time(NULL));
	if (data) {
		ast_str_append(&tmp, 0, ",%s", data);
	}

	fprintf(handle, "%s\n", ast_str_buffer(tmp));
	ast_debug(1, "sent '%s'\n", ast_str_buffer(tmp));
	ast_free(tmp);
}
