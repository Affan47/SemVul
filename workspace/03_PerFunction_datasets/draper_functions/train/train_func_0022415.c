do_p1_label(FILE *infile, FILE *outfile)
#endif
{
    int status;
    ftnint stateno;
    struct Labelblock *L;
    char *fmt;

    status = p1getd (infile, &stateno);

    if (status == EOF)
	err ("do_p1_label:  Missing label at end of file");
    else if (status == 0)
	err ("do_p1_label:  Missing label in p1 file ");
    else if (stateno < 0) {
	margin_printf(outfile, "\n%s:\n", user_label(stateno));
	last_was_label = 1;
	}
    else {
	L = labeltab + stateno;
	if (L->labused) {
		fmt = "%s:\n";
		last_was_label = 1;
		}
	else
		fmt = "/* %s: */\n";
	margin_printf(outfile, fmt, user_label(L->stateno));
    }
}
