load_config(json_conf_t *config, const char *file)
{
	int fd, rc, mode, lineno = 1;
	struct stat st;
	FILE *f;
	char buf[128];

	clear_config(config);


	mode = O_RDONLY;
	rc = open(file, mode);
	if (rc < 0) {
		if (errno != ENOENT) {
			syslog(LOG_ERR, "Error opening %s (%s)", file,
				strerror(errno));
			return 1;
		}
		syslog(LOG_WARNING,
			"Config file %s doesn't exist", file);
		return 1;
	}
	fd = rc;


	if (fstat(fd, &st) < 0) {
		syslog(LOG_ERR, "Error fstat'ing config file (%s)",
			strerror(errno));
		close(fd);
		return 1;
	}
	if ((st.st_mode & S_IWOTH) == S_IWOTH) {
		syslog(LOG_ERR, "Error - %s is world writable",
			file);
		close(fd);
		return 1;
	}
	if (!S_ISREG(st.st_mode)) {
		syslog(LOG_ERR, "Error - %s is not a regular file",
			file);
		close(fd);
		return 1;
	}


	f = fdopen(fd, "r");
	if (f == NULL) {
		syslog(LOG_ERR, "Error - fdopen failed (%s)",
			strerror(errno));
		close(fd);
		return 1;
	}

	while (get_line(f, buf)) {

		const struct kw_pair *kw;
		struct nv_pair nv;
		rc = nv_split(buf, &nv);
		switch (rc) {
			case 0:
				break;
			case 1:
				syslog(LOG_ERR,
				"Wrong number of arguments for line %d in %s",
					lineno, file);
				break;
			case 2:
				syslog(LOG_ERR,
					"Missing equal sign for line %d in %s",
					lineno, file);
				break;
			default:
				syslog(LOG_ERR,
					"Unknown error for line %d in %s",
					lineno, file);
				break;
		}
		if (nv.name == NULL) {
			lineno++;
			continue;
		}
		if (nv.value == NULL) {
			fclose(f);
			return 1;
		}


		kw = kw_lookup(nv.name);
		if (kw->name == NULL) {
			syslog(LOG_ERR,
				"Unknown keyword \"%s\" in line %d of %s",
				nv.name, lineno, file);
			fclose(f);
			return 1;
		}


		if (kw->max_options == 0 && nv.option != NULL) {
			syslog(LOG_ERR,
				"Keyword \"%s\" has invalid option "
				"\"%s\" in line %d of %s",
				nv.name, nv.option, lineno, file);
			fclose(f);
			return 1;
		}


		rc = kw->parser(&nv, lineno, config);
		if (rc != 0) {
			fclose(f);
			return 1;
		}

		lineno++;
	}

	fclose(f);
	return 0;
}
