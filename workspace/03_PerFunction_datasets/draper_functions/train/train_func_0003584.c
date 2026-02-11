ast_format_cap_remove(struct ast_format_cap *cap, struct ast_format *format)
{
	struct ast_format *fremove;

	fremove = ao2_callback(cap->formats, OBJ_POINTER | OBJ_UNLINK, find_exact_cb, format);
	if (fremove) {
		ao2_ref(fremove, -1);
		return 0;
	}

	return -1;
}
