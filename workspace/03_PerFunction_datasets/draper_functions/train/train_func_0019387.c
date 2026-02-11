print_signames(void)
{
	unsigned signo;

	for (signo = 1; signo < ARRAY_SIZE(signals); signo++) {
		const char *name = signals[signo];
		if (name[0])
			puts(name);
	}
}
