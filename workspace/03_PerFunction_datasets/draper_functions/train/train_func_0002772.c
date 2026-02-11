print_core(int state)
{
    register int i;
    register int k;
    register int rule;
    register core *statep;
    register Yshort *sp;
    register Yshort *sp1;

    statep = state_table[state];
    k = statep->nitems;

    for (i = 0; i < k; i++)
    {
	sp1 = sp = ritem + statep->items[i];

	while (*sp >= 0) ++sp;
	rule = -(*sp);
	fprintf(verbose_file, "\t%s : ", symbol_name[rlhs[rule]]);

        for (sp = ritem + rrhs[rule]; sp < sp1; sp++)
	    fprintf(verbose_file, "%s ", symbol_name[*sp]);

	putc('.', verbose_file);

	while (*sp >= 0)
	{
	    fprintf(verbose_file, " %s", symbol_name[*sp]);
	    sp++;
	}
	fprintf(verbose_file, "  (%d)\n", -2 - *sp);
    }
}
