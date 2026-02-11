pat_ref_read_from_file_smp(struct pat_ref *ref, const char *filename, char **err)
{
	FILE *file;
	char *c;
	int ret = 0;
	int line = 0;
	char *key_beg;
	char *key_end;
	char *value_beg;
	char *value_end;

	file = fopen(filename, "r");
	if (!file) {
		memprintf(err, "failed to open pattern file <%s>", filename);
		return 0;
	}


	while (fgets(trash.str, trash.size, file) != NULL) {
		line++;
		c = trash.str;


		if (*c == '#')
			continue;


		while (*c == ' ' || *c == '\t')
			c++;


		if (*c == '\0' || *c == '\r' || *c == '\n')
			continue;


		key_beg = c;
		while (*c && *c != ' ' && *c != '\t' && *c != '\n' && *c != '\r')
			c++;

		key_end = c;


		while (*c == ' ' || *c == '\t')
			c++;


		value_beg = c;
		while (*c && *c != '\n' && *c != '\r')
			c++;
		value_end = c;


		while (value_end > value_beg && (value_end[-1] == ' ' || value_end[-1] == '\t'))
			value_end--;


		*key_end = '\0';
		*value_end = '\0';


		if (!pat_ref_append(ref, key_beg, value_beg, line)) {
			memprintf(err, "out of memory");
			goto out_close;
		}
	}


	ret = 1;

 out_close:
	fclose(file);
	return ret;
}
