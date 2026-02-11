shell_free(struct gnutella_shell *sh)
{
	g_assert(sh);
	g_assert(SHELL_MAGIC == sh->magic);
	g_assert(NULL == sh->socket);
	g_assert(NULL == sh->output);
	HFREE_NULL(sh->msg);
	HFREE_NULL(sh->pending.msg);

	sh->magic = 0;
	WFREE(sh);
}
