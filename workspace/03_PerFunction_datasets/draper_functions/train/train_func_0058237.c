convert_to_working_tree_internal(const char *path, const char *src,
					    size_t len, struct strbuf *dst,
					    int normalizing)
{
	struct git_attr_check check[5];
	enum action action = CRLF_GUESS;
	enum eol eol_attr = EOL_UNSET;
	int ident = 0, ret = 0;
	const char *filter = NULL;

	setup_convert_check(check);
	if (!git_checkattr(path, ARRAY_SIZE(check), check)) {
		struct convert_driver *drv;
		action = git_path_check_crlf(path, check + 4);
		if (action == CRLF_GUESS)
			action = git_path_check_crlf(path, check + 0);
		ident = git_path_check_ident(path, check + 1);
		drv = git_path_check_convert(path, check + 2);
		eol_attr = git_path_check_eol(path, check + 3);
		if (drv && drv->smudge)
			filter = drv->smudge;
	}

	ret |= ident_to_worktree(path, src, len, dst, ident);
	if (ret) {
		src = dst->buf;
		len = dst->len;
	}


	if (filter || !normalizing) {
		action = determine_action(action, eol_attr);
		ret |= crlf_to_worktree(path, src, len, dst, action);
		if (ret) {
			src = dst->buf;
			len = dst->len;
		}
	}
	return ret | apply_filter(path, src, len, dst, filter);
}
