get_Cert_dir(char *cdir_in, char **tmp_in) {
	char *cdir, *home, *tmp;
	struct stat sbuf;
	int i;
	char *cases1[] = {"/.vnc", "/.vnc/certs", "/.vnc/certs/CA"};
	char *cases2[] = {"", "/CA", "/tmp"};

	if (cdir_in != NULL) {
		cdir = cdir_in;
	} else {
		cdir = ssl_certs_dir;
	}

	if (cdir == NULL) {
		home = get_home_dir();
		if (! home) {
			return NULL;
		}
		cdir = (char *) malloc(strlen(home) + strlen("/.vnc/certs/CA") + 1);
		for (i=0; i<3; i++) {
			sprintf(cdir, "%s%s", home, cases1[i]);
			if (stat(cdir, &sbuf) != 0) {
				rfbLog("creating dir: %s\n", cdir);
				if (mkdir(cdir, 0755) != 0) {
					rfbLog("could not create directory %s\n", cdir);
					rfbLogPerror("mkdir");
					return NULL;
				}
			} else if (! S_ISDIR(sbuf.st_mode)) {
				rfbLog("not a directory: %s\n", cdir);
				return NULL;
			}
		}
		sprintf(cdir, "%s%s", home, cases1[1]);
	}

	tmp = (char *) malloc(strlen(cdir) + strlen("/tmp") + 1);
	for (i=0; i<3; i++) {
		int ret;
		sprintf(tmp, "%s%s", cdir, cases2[i]);
		if (stat(tmp, &sbuf) != 0) {
			rfbLog("creating dir: %s\n", tmp);
			if (! strcmp(cases2[i], "/tmp")) {
				ret = mkdir(tmp, 0700);
			} else {
				ret = mkdir(tmp, 0755);
			}

			if (ret != 0) {
				rfbLog("could not create directory %s\n", tmp);
				rfbLogPerror("mkdir");
				return NULL;
			}
		} else if (! S_ISDIR(sbuf.st_mode)) {
			rfbLog("not a directory: %s\n", tmp);
			return NULL;
		}
	}
	sprintf(tmp, "%s/tmp", cdir);
	*tmp_in = tmp;
	return cdir;
}
