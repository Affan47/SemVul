report_import_html_stylesheet(const seaudit_log_t * log, const seaudit_report_t * report, FILE * outfile)
{
	char line[LINE_MAX], *line_ptr = NULL;
	FILE *fp;

	if (report->use_stylesheet) {
		fp = fopen(report->stylesheet, "r");
		if (fp == NULL) {
			WARN(log, "Cannot open stylesheet file %s.", report->stylesheet);
			return 1;
		}
		fprintf(outfile, "<style type=\"text/css\">\n");

		while (fgets(line, LINE_MAX, fp) != NULL) {
			free(line_ptr);
			line_ptr = NULL;
			if ((line_ptr = strdup(line)) == NULL) {
				int error = errno;
				free(line_ptr);
				fclose(fp);
				ERR(log, "%s", strerror(error));
				errno = error;
				return -1;
			}
			apol_str_trim(line_ptr);
			if (line_ptr[0] == '#' || apol_str_is_only_white_space(line_ptr))
				continue;
			fprintf(outfile, "%s\n", line_ptr);
		}
		fprintf(outfile, "</style>\n");
		fclose(fp);
		free(line_ptr);
	}
	return 0;
}
