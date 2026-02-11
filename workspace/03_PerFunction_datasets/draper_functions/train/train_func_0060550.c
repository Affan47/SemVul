__httpd_generate_dir_list(char *dir, char *buff, char *filen) {
#define WR_CODE(MSG, ...) do { \
	char *_msg = MSG; \
	sprintf(buff, MSG,##__VA_ARGS__); \
	fwrite(buff, 1, strlen(buff), fp); } while(0)

	FILE *fp;
	DIR *fdir;
	struct dirent *ent;
	struct stat st;
	char datestring[256];
	struct tm *tm;

	fdir = opendir(dir);
	if (fdir == NULL)
		return FALSE;

	srand(time(NULL));
	sprintf(filen, "%s/index_%d_%d.html", dir, time(NULL), rand());

	fp = fopen(filen, "w+");
	WR_CODE("<html><body>");

	while (ent = readdir(fdir)) {
		if (!strstr(filen, ent->d_name)) {
			sprintf(buff, "%s/%s", ent->d_name);
			stat(buff, &st);
			WR_CODE("<a href=\"%s\">%s</a> ", ent->d_name, ent->d_name);
			tm = localtime(&st.st_mtime);
			strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
			WR_CODE(" %s ", datestring);
			WR_CODE("<br/>");
		}
	}

	WR_CODE("</body></html>");
	fclose(fp);
	closedir(fdir);

	return TRUE;
}
