parse_source_files(const char *objfile, struct md4_ctx *md)
{
	char *cmd, *file, *line, *dir;
	const char *base;
	unsigned long flen, pos = 0;
	int dirlen, ret = 0, check_files = 0;

	cmd = NOFAIL(malloc(strlen(objfile) + sizeof("..cmd")));

	base = strrchr(objfile, '/');
	if (base) {
		base++;
		dirlen = base - objfile;
		sprintf(cmd, "%.*s.%s.cmd", dirlen, objfile, base);
	} else {
		dirlen = 0;
		sprintf(cmd, ".%s.cmd", objfile);
	}
	dir = NOFAIL(malloc(dirlen + 1));
	strncpy(dir, objfile, dirlen);
	dir[dirlen] = '\0';

	file = grab_file(cmd, &flen);
	if (!file) {
		warn("could not find %s for %s\n", cmd, objfile);
		goto out;
	}


	while ((line = get_next_line(&pos, file, flen)) != NULL) {
		char* p = line;
		if (strncmp(line, "deps_", sizeof("deps_")-1) == 0) {
			check_files = 1;
			continue;
		}
		if (!check_files)
			continue;


		if ( *(p + strlen(p)-1) != '\\')
			break;

		while (*p) {
                       if (isspace(*p)) {
				*p = '\0';
				break;
			}
			p++;
		}


		if ((strstr(line, dir)+strlen(dir)-1) == strrchr(line, '/')) {
			if (!parse_file(line, md)) {
				warn("could not open %s: %s\n",
				     line, strerror(errno));
				goto out_file;
			}

		}

	}


	ret = 1;
out_file:
	release_file(file, flen);
out:
	free(dir);
	free(cmd);
	return ret;
}
