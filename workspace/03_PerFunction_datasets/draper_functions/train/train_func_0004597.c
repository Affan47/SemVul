print_logs(void) {
	if (trackdir) {
		DIR *dir = opendir(trackdir);
		if (dir) {
			struct dirent *dp;
			while ( (dp = readdir(dir)) != NULL) {
				FILE *f;
				char *name = dp->d_name;
				if (!strcmp(name, ".") || !strcmp(name, "..")) {
					continue;
				}
				if (strstr(name, "0x") != name) {
					continue;
				}
				if (strstr(name, ".log") == NULL) {
					continue;
				}
				sprintf(tracktmp, "%s/%s", trackdir, name);
				f = fopen(tracktmp, "r");
				if (f) {
					char line[1024];
					fprintf(stderr, "===== x11vnc log %s =====\n", tracktmp);
					while (fgets(line, sizeof(line), f) != NULL) {
						fprintf(stderr, "%s", line);
					}
					fprintf(stderr, "\n");
					ff();
					fclose(f);
				}
			}
			closedir(dir);
		}
	}
}
