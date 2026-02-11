printQuery(const PGresult *result, const printQueryOpt *opt, FILE *fout, FILE *flog)
{
	printTableContent cont;
	int			i,
				r,
				c;

	if (cancel_pressed)
		return;

	printTableInit(&cont, &opt->topt, opt->title,
				   PQnfields(result), PQntuples(result));

	for (i = 0; i < cont.ncolumns; i++)
	{
		char		align;
		Oid			ftype = PQftype(result, i);

		switch (ftype)
		{
			case INT2OID:
			case INT4OID:
			case INT8OID:
			case FLOAT4OID:
			case FLOAT8OID:
			case NUMERICOID:
			case OIDOID:
			case XIDOID:
			case CIDOID:
			case CASHOID:
				align = 'r';
				break;
			default:
				align = 'l';
				break;
		}

		printTableAddHeader(&cont, PQfname(result, i),
							opt->translate_header, align);
	}


	for (r = 0; r < cont.nrows; r++)
	{
		for (c = 0; c < cont.ncolumns; c++)
		{
			char	   *cell;
			bool		mustfree = false;
			bool		translate;

			if (PQgetisnull(result, r, c))
				cell = opt->nullPrint ? opt->nullPrint : "";
			else
			{
				cell = PQgetvalue(result, r, c);
				if (cont.aligns[c] == 'r' && opt->topt.numericLocale)
				{
					cell = format_numeric_locale(cell);
					mustfree = true;
				}
			}

			translate = (opt->translate_columns && opt->translate_columns[c]);
			printTableAddCell(&cont, cell, translate, mustfree);
		}
	}


	if (opt->footers)
	{
		char	  **footer;

		for (footer = opt->footers; *footer; footer++)
			printTableAddFooter(&cont, *footer);
	}
	else if (!opt->topt.expanded && opt->default_footer)
	{
		unsigned long total_records;
		char		default_footer[100];

		total_records = opt->topt.prior_records + cont.nrows;
		snprintf(default_footer, sizeof(default_footer),
				 ngettext("(%lu row)", "(%lu rows)", total_records),
				 total_records);

		printTableAddFooter(&cont, default_footer);
	}

	printTable(&cont, fout, flog);
	printTableCleanup(&cont);
}
