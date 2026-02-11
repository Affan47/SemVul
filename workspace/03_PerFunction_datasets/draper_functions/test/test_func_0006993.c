mime_bound_check(char *line, int linelen, char *bound, int blen)
{
	if(linelen == -1) linelen = strlen(line);
	if(blen == -1) blen = strlen(bound);

	if(blen + 2 > linelen) return 0;

	if(!strncmp(line, "--", 2) && !strncmp(line + 2, bound, blen)) {
		if(!strncmp(line + blen + 2, "--", 2)) return 2;
		else return 1;
	}
	return 0;
}
