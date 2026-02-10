print_troff_ms_text(const printTableContent *cont, FILE *fout)
{
	bool		opt_tuples_only = cont->opt->tuples_only;
	unsigned short opt_border = cont->opt->border;
	unsigned int i;
	const char *const * ptr;

	if (cancel_pressed)
		return;

	if (opt_border > 2)
		opt_border = 2;

	if (cont->opt->start_table)
	{

		if (!opt_tuples_only && cont->title)
		{
			fputs(".LP\n.DS C\n", fout);
			troff_ms_escaped_print(cont->title, fout);
			fputs("\n.DE\n", fout);
		}


		fputs(".LP\n.TS\n", fout);
		if (opt_border == 2)
			fputs("center box;\n", fout);
		else
			fputs("center;\n", fout);

		for (i = 0; i < cont->ncolumns; i++)
		{
			fputc(*(cont->aligns + i), fout);
			if (opt_border > 0 && i < cont->ncolumns - 1)
				fputs(" | ", fout);
		}
		fputs(".\n", fout);


		if (!opt_tuples_only)
		{
			for (i = 0, ptr = cont->headers; i < cont->ncolumns; i++, ptr++)
			{
				if (i != 0)
					fputc('\t', fout);
				fputs("\\fI", fout);
				troff_ms_escaped_print(*ptr, fout);
				fputs("\\fP", fout);
			}
			fputs("\n_\n", fout);
		}
	}


	for (i = 0, ptr = cont->cells; *ptr; i++, ptr++)
	{
		troff_ms_escaped_print(*ptr, fout);

		if ((i + 1) % cont->ncolumns == 0)
		{
			fputc('\n', fout);
			if (cancel_pressed)
				break;
		}
		else
			fputc('\t', fout);
	}

	if (cont->opt->stop_table)
	{
		printTableFooter *footers = footers_with_default(cont);

		fputs(".TE\n.DS L\n", fout);


		if (footers && !opt_tuples_only && !cancel_pressed)
		{
			printTableFooter *f;

			for (f = footers; f; f = f->next)
			{
				troff_ms_escaped_print(f->data, fout);
				fputc('\n', fout);
			}
		}

		fputs(".DE\n", fout);
	}
}
