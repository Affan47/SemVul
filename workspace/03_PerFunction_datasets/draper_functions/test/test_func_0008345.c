report_to_table(FILE *inf, FILE *outf, char *format)
{
	struct col_format cfmt[TABLE_MAX_FIELDS];
	char line[MAX_TBL_LINE];
	int i, n = 0, f = 0, ncol, opt, c;
	struct stf *stf;
	GList *stars, *sl;
	struct cat_star *cats;
	double minres=HUGE, maxres=-HUGE, sumres=0.0, sumsqres=0.0, nres=0.0;

	srandom(time(NULL));

	if (format == NULL)
		format = P_STR(FILE_TAB_FORMAT);
	ncol = parse_tab_format(format, cfmt, TABLE_MAX_FIELDS, &opt);


	tab_snprint_star(line, MAX_TBL_LINE, NULL, NULL, 0, cfmt, ncol);
	if (opt & TAB_OPTION_COLLIST) {
		c = 0;
		for (i = 0; i < ncol; i++) {
			c += tab_snprint_coldesc(line, MAX_TBL_LINE, cfmt+i, c);
			fprintf(outf, "# %s\n", line);
		}
		fprintf(outf, "\n");
	}
	if (opt & TAB_OPTION_TABLEHEAD) {
		tab_snprint_head(line, MAX_TBL_LINE, cfmt, ncol);
		fprintf(outf, "%s\n\n", line);
	}

	do {
		stf = stf_read_frame(inf);
		if (stf == NULL)
			break;
		stars = stf_find_glist(stf, 0, SYM_STARS);
		if (stars == NULL) {
			stf_free_all(stf);
			continue;
		}
		f++;
		minres=HUGE; maxres=-HUGE; sumres=0.0; sumsqres=0.0; nres=0.0;
		for (sl = stars; sl != NULL; sl = sl->next) {
			cats = CAT_STAR(sl->data);
			if (cats->flags & INFO_RESIDUAL) {
				nres += 1;
				if (cats->residual > maxres)
					maxres = cats->residual;
				if (cats->residual < minres)
					minres = cats->residual;
				sumres += cats->residual;
				sumsqres += sqr(cats->residual);
			}
			tab_snprint_star(line, MAX_TBL_LINE, cats, stf, f, cfmt, ncol);
			fprintf(outf, "%s\n", line);
			n++;
		}
		if (opt & TAB_OPTION_RESSTATS && nres > 0) {
			fprintf(outf, "# residuals min:%.3f max:%.3f avg:%.4f sd:%.4f\n",
				minres, maxres, sumres / nres,
				sqrt((sumsqres - sqr(sumres) / nres) / nres));

		}
		stf_free_all(stf);
	} while (stf != NULL);
}
