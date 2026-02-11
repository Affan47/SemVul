set_process_env()
{
	static const char tcn[] = "TERMCAP";
	const char *tc = getenv(tcn);

	if (tc != NULL && tc[0] != '/')
		junsetenv(tcn);
#ifndef IPROC_TERM
	junsetenv("TERM");
#else
	jputenv(IPROC_TERM);
#endif
	jputenv("EMACS=t");
}
