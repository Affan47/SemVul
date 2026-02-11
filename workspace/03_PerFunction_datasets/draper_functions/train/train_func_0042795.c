short_kmbcf(char *str) {
	int i, saw_k = 0, saw_m = 0, saw_b = 0, saw_c = 0, saw_f = 0, n = 10;
	char *p, tmp[10];

	for (i=0; i<n; i++) {
		tmp[i] = '\0';
	}

	p = str;
	i = 0;
	while (*p) {
		if ((*p == 'K' || *p == 'k') && !saw_k) {
			tmp[i++] = 'K';
			saw_k = 1;
		} else if ((*p == 'M' || *p == 'm') && !saw_m) {
			tmp[i++] = 'M';
			saw_m = 1;
		} else if ((*p == 'B' || *p == 'b') && !saw_b) {
			tmp[i++] = 'B';
			saw_b = 1;
		} else if ((*p == 'C' || *p == 'c') && !saw_c) {
			tmp[i++] = 'C';
			saw_c = 1;
		} else if ((*p == 'F' || *p == 'f') && !saw_f) {
			tmp[i++] = 'F';
			saw_f = 1;
		}
		p++;
	}
	return(strdup(tmp));
}
