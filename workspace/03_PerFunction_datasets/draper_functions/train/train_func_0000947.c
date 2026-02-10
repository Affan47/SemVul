fixmatch(const char *pattern, char *line, int ignore_case, regmatch_t *match)
{
	char *hit;
	if (ignore_case)
		hit = strcasestr(line, pattern);
	else
		hit = strstr(line, pattern);

	if (!hit) {
		match->rm_so = match->rm_eo = -1;
		return REG_NOMATCH;
	}
	else {
		match->rm_so = hit - line;
		match->rm_eo = match->rm_so + strlen(pattern);
		return 0;
	}
}
