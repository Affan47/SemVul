optusage(arg0, args, optlist)
CONST char *arg0, *args;
CONST opt_t *optlist;
{
	int n;

	fprintf(stderr, "Usage: %s", arg0);
	n = 0;
	if (optlist) while (optlist[n].opt) n++;
	if (n > 0) {
		fputs(" [-", stderr);
		for (n = 0; optlist[n].opt; n++) {
			fputc(optlist[n].opt, stderr);

			if (!(optlist[n].argval)) continue;
			fprintf(stderr, " <%s>", optlist[n].argval);
			if (optlist[n + 1].opt) fputs(" [-", stderr);
		}
		fputc(']', stderr);
	}
	fprintf(stderr, " %s\n", args);
}
