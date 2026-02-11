manager_dbdel(struct mansession *s, const struct message *m)
{
	const char *family = astman_get_header(m, "Family");
	const char *key = astman_get_header(m, "Key");
	int res;

	if (ast_strlen_zero(family)) {
		astman_send_error(s, m, "No family specified.");
		return 0;
	}

	if (ast_strlen_zero(key)) {
		astman_send_error(s, m, "No key specified.");
		return 0;
	}

	res = ast_db_del(family, key);
	if (res)
		astman_send_error(s, m, "Database entry not found");
	else
		astman_send_ack(s, m, "Key deleted successfully");

	return 0;
}
