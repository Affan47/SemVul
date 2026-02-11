ns_os_openfile(const char *filename, mode_t mode, isc_boolean_t switch_user) {
	char strbuf[ISC_STRERRORSIZE], *f;
	FILE *fp;
	int fd;


	f = strdup(filename);
	if (f == NULL) {
		isc__strerror(errno, strbuf, sizeof(strbuf));
		ns_main_earlywarning("couldn't strdup() '%s': %s",
				     filename, strbuf);
		return (NULL);
	}
	if (mkdirpath(f, ns_main_earlywarning) == -1) {
		free(f);
		return (NULL);
	}
	free(f);

	if (switch_user && runas_pw != NULL) {
#ifndef HAVE_LINUXTHREADS
		gid_t oldgid = getgid();
#endif

		setperms(runas_pw->pw_uid, runas_pw->pw_gid);

		fd = safe_open(filename, mode, ISC_FALSE);

#ifndef HAVE_LINUXTHREADS

		setperms(0, oldgid);
#endif

		if (fd == -1) {
#ifndef HAVE_LINUXTHREADS
			fd = safe_open(filename, mode, ISC_FALSE);
			if (fd != -1) {
				ns_main_earlywarning("Required root "
						     "permissions to open "
						     "'%s'.", filename);
			} else {
				ns_main_earlywarning("Could not open "
						     "'%s'.", filename);
			}
			ns_main_earlywarning("Please check file and "
					     "directory permissions "
					     "or reconfigure the filename.");
#else
			ns_main_earlywarning("Could not open "
					     "'%s'.", filename);
			ns_main_earlywarning("Please check file and "
					     "directory permissions "
					     "or reconfigure the filename.");
#endif
		}
	} else {
		fd = safe_open(filename, mode, ISC_FALSE);
	}

	if (fd < 0) {
		isc__strerror(errno, strbuf, sizeof(strbuf));
		ns_main_earlywarning("could not open file '%s': %s",
				     filename, strbuf);
		return (NULL);
	}

	fp = fdopen(fd, "w");
	if (fp == NULL) {
		isc__strerror(errno, strbuf, sizeof(strbuf));
		ns_main_earlywarning("could not fdopen() file '%s': %s",
				     filename, strbuf);
	}

	return (fp);
}
