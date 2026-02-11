dialgroup_refreshdb(struct ast_channel *chan, const char *cdialgroup)
{
	int len = 500, res = 0;
	char *buf = NULL;
	char *new_buf;
	char *dialgroup = ast_strdupa(cdialgroup);

	do {
		len *= 2;
		new_buf = ast_realloc(buf, len);
		if (!new_buf) {
			ast_free(buf);
			return -1;
		}
		buf = new_buf;

		if ((res = dialgroup_read(chan, "", dialgroup, buf, len)) < 0) {
			ast_free(buf);
			return -1;
		}
	} while (res == 1);

	if (ast_strlen_zero(buf)) {
		ast_db_del("dialgroup", cdialgroup);
	} else {
		ast_db_put("dialgroup", cdialgroup, buf);
	}
	ast_free(buf);
	return 0;
}
