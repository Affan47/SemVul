get_cols_rows(const t_gems_msg * msg, int *cols, int *rows)
{
	if ((msg->type != GEMS_WINSIZE) || (msg->len != 2 * sizeof(int)))
		return FAIL;

	*cols = ((int *) msg->data)[0];
	*rows = ((int *) msg->data)[1];

	return TRUE;
}
