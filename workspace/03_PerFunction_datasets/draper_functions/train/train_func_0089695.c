tt_new_table(int flags)
{
	struct tt *tb;

	tb = calloc(1, sizeof(struct tt));
	if (!tb)
		return NULL;

	tb->flags = flags;
	INIT_LIST_HEAD(&tb->tb_lines);
	INIT_LIST_HEAD(&tb->tb_columns);

#if defined(HAVE_WIDECHAR)
	if (!(flags & TT_FL_ASCII) && !strcmp(nl_langinfo(CODESET), "UTF-8"))
		tb->symbols = &utf8_tt_symbols;
	else
#endif
		tb->symbols = &ascii_tt_symbols;

	tb->first_run = TRUE;
	return tb;
}
