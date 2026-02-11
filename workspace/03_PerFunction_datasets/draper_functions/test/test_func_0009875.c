ReadConfig(const char *filename)
{
	FILE	*capFp;
	char	line[MAX_COLS], *p;
	char	buf[BUF_SIZE];
	struct capability *c;
	int	i;
	int	errors = 0;

	if ((capFp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Error: can't open config file\r\r\n");
		perror(filename);
		return FAILURE;
	}

	while(fgets(line, MAX_COLS, capFp) != NULL) {
	nextLabel:
		if ((p = strchr(line, '#')) != NULL)
			*p = '\0';
		if (strchr(line, ':') == NULL) continue;
		for (p = strtok(line, label_delim); p != NULL; p = strtok(NULL, label_delim)) {

			if ((c = FindCap(p)) != NULL) {

				char *l = buf;
				while (fgets(line, MAX_COLS, capFp) != NULL
				       && line[0] == '\t') {
					char *l2 = line;
					while (*l2 != '\n' && *l2 != '#') {
						*l++ = *l2++;
					}
					*l++ = '\n';
				}
				*l = '\0';
				if (! c->initialized) {

					if (c->arg) {
#ifdef	DEBUG
						fprintf(stderr, "Capability %s set to arg %s\r\n",
							c->name, c->arg);
#endif
						if (c->func(c->arg) < 0)
							errors++;
					} else {
#ifdef	DEBUG
						fprintf(stderr, "Capability %s set to %s",
							c->name, buf);
#endif
						if (c->func(buf) < 0)
							errors++;
					}
					c->initialized = 1;
				}
				goto nextLabel;
			}
		}
	}

	for (i = 0, c = cap; i < MAX_CAPS; i++, c++) {
		if ((c->name != NULL) && !c->initialized) {
			if (c->arg) {
#ifdef	DEBUG
				fprintf(stderr, "Capability %s defaults to arg %s\r\n", c->name, c->arg);
#endif
				if (c->func(c->arg) < 0)
					errors++;
			} else if (c->def_value) {
#ifdef	DEBUG
				fprintf(stderr, "Capability %s defaults to %s\r\n", c->name, c->def_value);
#endif
				if (c->func(c->def_value) < 0)
					errors++;
			} else {
				fprintf(stderr, "Error: entry for capability `%s' not found\r\r\n", c->name);
				errors++;
			}
		}
	}
	fclose(capFp);
#ifdef	DEBUG
	fprintf(stderr, "Finished reading config file\r\n");
#endif
	if (errors)
		return FAILURE;
	else
		return SUCCESS;
}
