include_file(const char * name) {
	struct stat st;
	DIR * d;
	struct dirent * r;
	char * fn;

	if (stat(name, &st)) {
		scan_err("warning: stat failed on %s: %s", name, strerror(errno));
	} else {
		if (S_ISDIR(st.st_mode)) {
			if ((d = opendir(name)) == NULL) {
				scan_err("warning: opendir failed on %s: %s", name, strerror(errno));
			} else {
				while ((r = readdir(d)) != NULL) {

					if (r->d_name[0] == '.')
						continue;
					asprintf(&fn, "%s/%s", name, r->d_name);
					include_file(fn);
					free(fn);
				}
				closedir(d);
			}
		} else
			step_into_include_file(name);
	}
}
