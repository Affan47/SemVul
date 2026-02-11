createHtml()
{
	char *fname;
	domain *d;
	int i;

	if ((fname = (char *)calloc(1024, sizeof(char))) == NULL) {
		fprintf(stderr, "cannot allocate memory: %s\n", strerror(errno));
		return;
	}

	for (i = 0; i < DomainsTab.nval; i++) {
		d = &DomainsTab.alldomains[i];
		snprintf(fname, 1024, "%s/%s/%d/%d/%d.html",
				outputdir,
				d->domain,
				cur_year,
				cur_month,
				cur_day);
		createDailyHtml(fname, d);
		snprintf(fname, 1024, "%s/%s/%d/%d/",
				outputdir,
				d->domain,
				cur_year,
				cur_month);
		createMonthlyHtml(fname, d->domain);
		snprintf(fname, 1024, "%s/%s/%d/",
				outputdir,
				d->domain,
				cur_year);
		createYearlyHtml(fname, d->domain);
		snprintf(fname, 1024, "%s/%s/",
				outputdir,
				d->domain);
		createDomainHtml(fname, d->domain);
	}

	snprintf(fname, 1024, "%s/general/%d/%d/%d.html",
			outputdir,
			cur_year,
			cur_month,
			cur_day);
	createGeneralDailyHtml(fname);
	snprintf(fname, 1024, "%s/general/%d/%d/",
			outputdir,
			cur_year,
			cur_month);
	createGeneralMonthlyHtml(fname);
	snprintf(fname, 1024, "%s/%s/%d/",
			outputdir,
			"general",
			cur_year);
	createGeneralYearlyHtml(fname);
	snprintf(fname, 1024, "%s/general/",
			outputdir);
	createGeneralHtml(fname);

	snprintf(fname, 1024, "%s/index.html",outputdir);
	createIndexHtml(fname);

	free(fname);
}
