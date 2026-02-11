ast_str_get_hint(struct ast_str **hint, ssize_t hintsize, struct ast_str **name, ssize_t namesize, struct ast_channel *c, const char *context, const char *exten)
{
	struct ast_exten *e = ast_hint_extension(c, context, exten);

	if (!e) {
		return 0;
	}

	if (hint) {
		ast_str_set(hint, hintsize, "%s", ast_get_extension_app(e));
	}
	if (name) {
		const char *tmp = ast_get_extension_app_data(e);
		if (tmp) {
			ast_str_set(name, namesize, "%s", tmp);
		}
	}
	return -1;
}
