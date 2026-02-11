bb__parsepwent(void *data, char *line)
{
	char *endptr;
	char *p;
	int i;

	i = 0;
	while (1) {
		p = (char *) data + pw_off[i];

		if (i < 2 || i > 3) {
			*((char **) p) = line;
			if (i == 6) {
				return 0;
			}


			line = strchr(line, ':');
			if (!line) {
				break;
			}
		} else {
			unsigned long t = strtoul(line, &endptr, 10);


			if ((endptr == line) || (*endptr != ':')) {
				break;
			}
			line = endptr;
			if (i & 1) {
				*((gid_t *) p) = t;
			} else {
				*((uid_t *) p) = t;
			}
		}

		*line++ = '\0';
		i++;
	}

	return -1;
}
