colon_n(char *line) {
	char *q;
	int n;
	q = strrchr(line, ':');
	if (! q) {
		return 0;
	}
	q = lblanks(q+1);
	if (sscanf(q, "%d", &n) == 1) {
		return n;
	}
	return 0;
}
