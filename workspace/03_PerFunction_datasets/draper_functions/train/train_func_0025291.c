print_info(FILE *fp, struct vs_recipy *vs, struct ccd_frame *fr)
{
	FITS_row *cp;
	int ret;
	int ds, df;
	double jd = 0.0;

	if (fr == NULL)
		return;
	if (string_has(vs->repinfo, 'f')) {
		fprintf(fp, "%s", fr->name);
		if (string_has(vs->repinfo, 't')) {
			if (string_has(vs->repstar, 'd'))
				fprintf(fp, ", ");
			else
				fprintf(fp, " ");
			cp = fits_keyword_lookup(fr, "JDATE");
			if (cp != NULL) {
				if ((ret=sscanf((char *)cp, "%*s = %d.%d", &ds, &df)) == 2)
					jd = 1.0 * ds + df / (pow(10, ceil(log10(df*1.0))));
				else
					jd = 0.0;
			}
			fprintf(fp, " %16.8f", jd);
		if (string_has(vs->repstar, 'd'))
			fprintf(fp, ", ");
		else
			fprintf(fp, " ");
		}
	} else {
		if (string_has(vs->repinfo, 't')) {
			cp = fits_keyword_lookup(fr, "JDATE");
			if (cp != NULL) {
				if ((ret=sscanf((char *)cp, "%*s = %d.%d", &ds, &df)) == 2)
					jd = 1.0 * ds + df / (pow(10, ceil(log10(df*1.0))));
				else
					jd = 0.0;
			}
			fprintf(fp, "%16.8f", jd);
		}
		if (string_has(vs->repstar, 'd'))
			fprintf(fp, ", ");
		else
			fprintf(fp, " ");
	}
}
