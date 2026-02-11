ifmodule_read(struct ast_channel *chan, const char *cmd, char *data,
		    char *buf, size_t len)
{
	char *ret = "0";

	*buf = '\0';

	if (data)
		if (ast_module_check(data))
			ret = "1";

	ast_copy_string(buf, ret, len);

	return 0;
}
