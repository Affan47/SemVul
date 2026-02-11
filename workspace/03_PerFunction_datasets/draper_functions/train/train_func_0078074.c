dolist(int (*callback_func)(const char *, const char *,
				       const char *, int,
				       struct gpg_list_info *),
		  int (*err_func)(const char *, size_t, void *),
		  void *voidarg)
{
	struct gpg_callbackinfo gci;
	struct gpg_callbacklistinfo gcli;
	int rc, rc2;

	close(libmail_gpg_stdin);
	libmail_gpg_stdin= -1;

	memset(&gci, 0, sizeof(gci));
	gci.err_func=err_func;
	gci.voidarg=voidarg;

	gci.line_func= &dolist_callback;
	gci.line_callback_arg= &gcli;

	memset(&gcli, 0, sizeof(gcli));
	gcli.callback_func=callback_func;

	rc=libmail_gpg_read( libmail_gpg_line_stdout,
			     libmail_gpg_line_stderr,
			     NULL,
			     0,
			     &gci);


	rc2= (*gci.line_func)(NULL, gci.line_callback_arg,
					  gci.voidarg);
	if (rc2)
		rc=rc2;

	if (gcli.keybuffer)
		free(gcli.keybuffer);

	if (gci.linebuffer)
		free(gci.linebuffer);
	return (rc);
}
