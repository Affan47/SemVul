gnuplot_process_file (gretlopt opt, PRN *prn)
{
    const char *inname = get_optval_string(GNUPLOT, OPT_D);
    FILE *fp, *fq;
    int err = 0;

    if (inname == NULL && *inname == '\0') {
	return E_DATA;
    }

    fp = gretl_fopen(inname, "r");
    if (fp == NULL) {
	return E_FOPEN;
    }

    fq = open_plot_input_file(PLOT_USER, &err);

    if (err) {
	fclose(fp);
    } else {
	char line[1024];

	while (fgets(line, sizeof line, fp)) {
	    fputs(line, fq);
	}

	fclose(fp);
	err = finalize_plot_input_file(fq);
    }

    return err;
}
