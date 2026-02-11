read_proc_swaps(void) {
	FILE *swaps;
	char line[1024];
	char *p, **q;
	size_t sz;

	numSwaps = 0;
	swapFiles = NULL;

	swaps = fopen(_PATH_PROC_SWAPS, "r");
	if (swaps == NULL)
		return;


	if (!fgets(line, sizeof(line), swaps)) {

		if (ferror(swaps))
			warn(_("%s: unexpected file format"), _PATH_PROC_SWAPS);
		fclose(swaps);
		return;
	}

	if (line[0] != '\0' && strncmp(line, "Filename\t", 9))
		goto valid_first_line;

	while (fgets(line, sizeof(line), swaps)) {
 valid_first_line:


		for (p = line; *p && *p != ' '; p++);
		*p = '\0';


		sz = strlen(line);
		if (sz > PATH_DELETED_SUFFIX_SZ) {
		       p = line + (sz - PATH_DELETED_SUFFIX_SZ);
		       if (strcmp(p, PATH_DELETED_SUFFIX) == 0)
			       *p = '\0';
		}

		q = realloc(swapFiles, (numSwaps+1) * sizeof(*swapFiles));
		if (q == NULL)
			break;
		swapFiles = q;

		if ((p = unmangle(line, NULL)) == NULL)
			break;

		swapFiles[numSwaps++] = canonicalize_path(p);
		free(p);
	}
	fclose(swaps);
}
