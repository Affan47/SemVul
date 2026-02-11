jobscmd(int argc, char **argv)
{
	int mode, m;
	struct output *out;

	mode = 0;
	while ((m = nextopt("lp")))
		if (m == 'l')
			mode = SHOW_PID;
		else
			mode = SHOW_PGID;

	out = out1;
	argv = argptr;
	if (*argv)
		do
			showjob(out, getjob(*argv,0), mode);
		while (*++argv);
	else
		showjobs(out, mode);

	return 0;
}
