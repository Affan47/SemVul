read_konfig()
{
	FILE *config;
	char *line, *ps, *pe;
	char opt[OPTNAME_MAX], val[VALUE_MAX];
	size_t line_len;

	config = fopen(KONFIG_PATH, "rw");
	if (config) {

		while (!feof(config)) {
			memset(opt, 0, OPTNAME_MAX);
			memset(val, 0, VALUE_MAX);
			line = NULL;
			line_len = 0;
			line_len = getline(&line, &line_len, config);
			line[line_len - 1] = 0;
			ps = line;
			while (*ps == ' ' || *ps == '\t') ps++;
			if (*ps == '#') continue;

			pe = strchr(ps, '=');
			if (!pe) continue;

			strncpy(opt, ps, pe-ps);
			strcpy(val, pe+1);
			if (kopt_setval(opt, val))
				printf("No such option: %s\n", opt);

			free(line);
		}
		fclose(config);
	}
}
