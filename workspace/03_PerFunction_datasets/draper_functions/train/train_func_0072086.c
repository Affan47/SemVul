complete(EditLine *el, int ch __attribute__((__unused__)))
{
	DIR *dd = opendir(".");
	struct dirent *dp;
	const char* ptr;
	const LineInfo *lf = el_line(el);
	size_t len;
	int res = CC_ERROR;


	for (ptr = lf->cursor - 1;
	    !isspace((unsigned char)*ptr) && ptr > lf->buffer; ptr--)
		continue;
	len = lf->cursor - ++ptr;

	for (dp = readdir(dd); dp != NULL; dp = readdir(dd)) {
		if (len > strlen(dp->d_name))
			continue;
		if (strncmp(dp->d_name, ptr, len) == 0) {
			if (el_insertstr(el, &dp->d_name[len]) == -1)
				res = CC_ERROR;
			else
				res = CC_REFRESH;
			break;
		}
	}

	closedir(dd);
	return res;
}
