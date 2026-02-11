scan_mode(const char *mode, int *omode)
{

	if (!strcmp(mode, "r")) {
		*omode = O_RDONLY;
	} else if (!strcmp(mode, "w")) {
		*omode = O_WRONLY | O_CREAT | O_TRUNC;
	} else if (!strcmp(mode, "wx")) {
		*omode = O_WRONLY | O_CREAT | O_EXCL;
	} else if (!strcmp(mode, "a")) {
		*omode = O_WRONLY | O_APPEND | O_CREAT;
	} else if (!strcmp(mode, "a+")) {
		*omode = O_RDWR | O_APPEND;
	} else if (!strcmp(mode, "r+")) {
		*omode = O_RDWR;
	} else if (!strcmp(mode, "w+")) {
		*omode = O_RDWR   | O_CREAT | O_EXCL;
	} else {
		fprintf(stderr, catgets(catd, CATSET, 152,
			"Internal error: bad stdio open mode %s\n"), mode);
		errno = EINVAL;
		return -1;
	}
	return 0;
}
