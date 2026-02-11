check_timerange(pval *p)
{
	char *times;
	char *e;
	int s1, s2;
	int e1, e2;

	times = ast_strdupa(p->u1.str);


	if (ast_strlen_zero(times) || !strcmp(times, "*")) {
		return;
	}

	e = strchr(times, '-');
	if (!e) {
		ast_log(LOG_WARNING, "Warning: file %s, line %d-%d: The time range format (%s) requires a '-' surrounded by two 24-hour times of day!\n",
				p->filename, p->startline, p->endline, times);
		warns++;
		return;
	}
	*e = '\0';
	e++;
	while (*e && !isdigit(*e))
		e++;
	if (!*e) {
		ast_log(LOG_WARNING, "Warning: file %s, line %d-%d: The time range format (%s) is missing the end time!\n",
				p->filename, p->startline, p->endline, p->u1.str);
		warns++;
	}
	if (sscanf(times, "%2d:%2d", &s1, &s2) != 2) {
		ast_log(LOG_WARNING, "Warning: file %s, line %d-%d: The start time (%s) isn't quite right!\n",
				p->filename, p->startline, p->endline, times);
		warns++;
	}
	if (sscanf(e, "%2d:%2d", &e1, &e2) != 2) {
		ast_log(LOG_WARNING, "Warning: file %s, line %d-%d: The end time (%s) isn't quite right!\n",
				p->filename, p->startline, p->endline, times);
		warns++;
	}

	s1 = s1 * 30 + s2/2;
	if ((s1 < 0) || (s1 >= 24*30)) {
		ast_log(LOG_WARNING, "Warning: file %s, line %d-%d: The start time (%s) is out of range!\n",
				p->filename, p->startline, p->endline, times);
		warns++;
	}
	e1 = e1 * 30 + e2/2;
	if ((e1 < 0) || (e1 >= 24*30)) {
		ast_log(LOG_WARNING, "Warning: file %s, line %d-%d: The end time (%s) is out of range!\n",
				p->filename, p->startline, p->endline, e);
		warns++;
	}
	return;
}
