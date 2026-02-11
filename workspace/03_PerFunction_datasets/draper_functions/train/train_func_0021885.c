print_latex_text(const printTableContent *cont, FILE *fout)
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
			fputs("\\begin{center}\n", fout);
			latex_escaped_print(cont->title, fout);
			fputs("\n\\end{center}\n\n", fout);
		}


		fputs("\\begin{tabular}{", fout);

		if (opt_border == 2)
			fputs("| ", fout);
		for (i = 0; i < cont->ncolumns; i++)
		{
			fputc(*(cont->aligns + i), fout);
			if (opt_border != 0 && i < cont->ncolumns - 1)
				fputs(" | ", fout);
		}
		if (opt_border == 2)
			fputs(" |", fout);

		fputs("}\n", fout);

		if (!opt_tuples_only && opt_border == 2)
			fputs("\\hline\n", fout);


		if (!opt_tuples_only)
		{
			for (i = 0, ptr = cont->headers; i < cont->ncolumns; i++, ptr++)
			{
				if (i != 0)
					fputs(" & ", fout);
				fputs("\\textit{", fout);
				latex_escaped_print(*ptr, fout);
				fputc('}', fout);
			}
			fputs(" \\\\\n", fout);
			fputs("\\hline\n", fout);
		}
	}


	for (i = 0, ptr = cont->cells; *ptr; i++, ptr++)
	{
		latex_escaped_print(*ptr, fout);

		if ((i + 1) % cont->ncolumns == 0)
		{
			fputs(" \\\\\n", fout);
			if (cancel_pressed)
				break;
		}
		else
			fputs(" & ", fout);
	}

	if (cont->opt->stop_table)
	{
		printTableFooter *footers = footers_with_default(cont);

		if (opt_border == 2)
			fputs("\\hline\n", fout);

		fputs("\\end{tabular}\n\n\\noindent ", fout);


		if (footers && !opt_tuples_only && !cancel_pressed)
		{
			printTableFooter *f;

			for (f = footers; f; f = f->next)
			{
				latex_escaped_print(f->data, fout);
				fputs(" \\\\\n", fout);
			}
		}

		fputc('\n', fout);
	}
}
