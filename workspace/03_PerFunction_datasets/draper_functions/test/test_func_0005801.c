PQprintTuples(const PGresult *res,
			  FILE *fout,
			  int PrintAttNames,
			  int TerseOutput,
			  int colWidth
)
{
	int			nFields;
	int			nTups;
	int			i,
				j;
	char		formatString[80];

	char	   *tborder = NULL;

	nFields = PQnfields(res);
	nTups = PQntuples(res);

	if (colWidth > 0)
		sprintf(formatString, "%%s %%-%ds", colWidth);
	else
		sprintf(formatString, "%%s %%s");

	if (nFields > 0)
	{

		if (!TerseOutput)
		{
			int			width;

			width = nFields * 14;
			tborder = malloc(width + 1);
			if (!tborder)
			{
				fprintf(stderr, libpq_gettext("out of memory\n"));
				exit(1);
			}
			for (i = 0; i <= width; i++)
				tborder[i] = '-';
			tborder[i] = '\0';
			fprintf(fout, "%s\n", tborder);
		}

		for (i = 0; i < nFields; i++)
		{
			if (PrintAttNames)
			{
				fprintf(fout, formatString,
						TerseOutput ? "" : "|",
						PQfname(res, i));
			}
		}

		if (PrintAttNames)
		{
			if (TerseOutput)
				fprintf(fout, "\n");
			else
				fprintf(fout, "|\n%s\n", tborder);
		}

		for (i = 0; i < nTups; i++)
		{
			for (j = 0; j < nFields; j++)
			{
				const char *pval = PQgetvalue(res, i, j);

				fprintf(fout, formatString,
						TerseOutput ? "" : "|",
						pval ? pval : "");
			}
			if (TerseOutput)
				fprintf(fout, "\n");
			else
				fprintf(fout, "|\n%s\n", tborder);
		}
	}

	if (tborder)
		free(tborder);
}
