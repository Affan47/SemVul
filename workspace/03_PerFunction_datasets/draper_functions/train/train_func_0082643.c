git_pager(void)
{
	const char *pager;

	if (!isatty(1))
		return NULL;

	pager = getenv("GIT_PAGER");
	if (!pager) {
		if (!pager_program)
			git_config(git_default_config, NULL);
		pager = pager_program;
	}
	if (!pager)
		pager = getenv("PAGER");
	if (!pager)
		pager = DEFAULT_PAGER;
	else if (!*pager || !strcmp(pager, "cat"))
		pager = NULL;

	return pager;
}
