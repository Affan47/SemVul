mnt_free_table(struct libmnt_table *tb)
{
	if (!tb)
		return;

	mnt_reset_table(tb);

	DBG(TAB, mnt_debug_h(tb, "free"));
	free(tb);
}
