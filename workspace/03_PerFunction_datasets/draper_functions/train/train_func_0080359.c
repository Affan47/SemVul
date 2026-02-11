tzload(const char *name, char *canonname, struct state * sp, bool doextend)
{
	union local_storage *lsp = malloc(sizeof *lsp);

	if (!lsp)
		return errno;
	else
	{
		int			err = tzloadbody(name, canonname, sp, doextend, lsp);

		free(lsp);
		return err;
	}
}
