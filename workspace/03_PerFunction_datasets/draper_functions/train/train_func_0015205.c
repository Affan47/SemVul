check_seq_number(char *file, int *sqn)
{
	struct dirent * entry;
	DIR *dir;
	char *filen;
	char *dirn;
	int lseq = 0;
	int sz, n;

	dirn = dirname(file);
	filen = basename(file);
	sz = strlen(filen);

	dir = opendir(dirn);
	if (dir == NULL) {


		d3_printf("check_seq_number: funny dir: %s\n", dirn);
		return 0;
	}
	while ((entry = readdir(dir))) {
		if (strncmp(entry->d_name, filen, sz))
			continue;
		n = strtol(entry->d_name + sz, NULL, 10);
		if (n > lseq)
			lseq = n;
	}
	closedir(dir);
	if (*sqn <= lseq) {
		d3_printf("check_seq_number: adjusting sqn to %d\n", lseq+1);
		*sqn = lseq + 1;
		return -1;
	}
	return 0;
}
