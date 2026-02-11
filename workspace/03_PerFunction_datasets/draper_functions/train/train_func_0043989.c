ast_bt_create(void)
{
	struct ast_bt *bt = ast_calloc(1, sizeof(*bt));
	if (!bt) {
		ast_log(LOG_ERROR, "Unable to allocate memory for backtrace structure!\n");
		return NULL;
	}

	bt->alloced = 1;

	ast_bt_get_addresses(bt);

	return bt;
}
