open_plot(FILE **fp, char *initial)
{
	FILE *plfp = NULL;
	char *fn;
	char qu[1024];

	if (!P_INT(FILE_PLOT_TO_FILE)) {
		plfp = popen(P_STR(FILE_GNUPLOT), "w");
		if (plfp != NULL && (long)plfp != -1) {
			if (fp)
				*fp = plfp;
			return 1;
		}
		err_printf("Cannot run gnuplot, prompting for file\n");
	}
	fn = modal_file_prompt("Select Plot File", initial);
	if (fn == NULL) {
		err_printf("Aborted\n");
		return -1;
	}
	if ((plfp = fopen(fn, "r")) != NULL) {
		snprintf(qu, 1023, "File %s exists\nOverwrite?", fn);
		if (!modal_yes_no(qu, "gcx: file exists")) {
			fclose(plfp);
			err_printf("Aborted\n");
			return -1;
		} else {
			fclose(plfp);
		}
	}
	plfp = fopen(fn, "w");
	if (plfp == NULL) {
		err_printf("Cannot create file %s (%s)", fn, strerror(errno));
		return -1;
	}
	if (fp)
		*fp = plfp;
	return 0;
}
