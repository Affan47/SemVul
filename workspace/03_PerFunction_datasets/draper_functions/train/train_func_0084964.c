print_latex_text(const char *title, const char *const * headers,
				 const char *const * cells, const char *const * footers,
				 const char *opt_align, const printTableOpt *opt,
				 FILE *fout)
{
	bool		opt_tuples_only = opt->tuples_only;
	unsigned short int opt_border = opt->border;
	unsigned int col_count = 0;
	unsigned int i;
	const char *const * ptr;

	if (cancel_pressed)
		return;

	if (opt_border > 2)
		opt_border = 2;


	for (ptr = headers; *ptr; ptr++)
		col_count++;

	if (opt->start_table)
	{

		if (!opt_tuples_only && title)
		{
			fputs("\\begin{center}\n", fout);
			latex_escaped_print(title, fout);
			fputs("\n\\end{center}\n\n", fout);
		}


		fputs("\\begin{tabular}{", fout);

		if (opt_border == 2)
			fputs("| ", fout);
		for (i = 0; i < col_count; i++)
		{
			fputc(*(opt_align + i), fout);
			if (opt_border != 0 && i < col_count - 1)
				fputs(" | ", fout);
		}
		if (opt_border == 2)
			fputs(" |", fout);

		fputs("}\n", fout);

		if (!opt_tuples_only && opt_border == 2)
			fputs("\\hline\n", fout);


		if (!opt_tuples_only)
		{
			for (i = 0, ptr = headers; i < col_count; i++, ptr++)
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


	for (i = 0, ptr = cells; *ptr; i++, ptr++)
	{
		latex_escaped_print(*ptr, fout);

		if ((i + 1) % col_count == 0)
		{
			fputs(" \\\\\n", fout);
			if (cancel_pressed)
				break;
		}
		else
			fputs(" & ", fout);
	}

	if (opt->stop_table)
	{
		if (opt_border == 2)
			fputs("\\hline\n", fout);

		fputs("\\end{tabular}\n\n\\noindent ", fout);


		if (footers && !opt_tuples_only && !cancel_pressed)
		{
			for (ptr = footers; *ptr; ptr++)
			{
				latex_escaped_print(*ptr, fout);
				fputs(" \\\\\n", fout);
			}
		}

		fputc('\n', fout);
	}
}
