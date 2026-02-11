page_file(FILE *stream)
{
	FILE *cmd;
	char buf[BUFSIZ+1];
	char *fgets_ret;


	fflush(stderr);
	fflush(stdout);
	fflush(stdin);


	if (pager == NULL || pager[0] == '\0') {
	    cmd = stdout;
	} else {
	    cmd = popen(pager, "w");
	}
	if (cmd == NULL) {
		fprintf(stderr, "unable form pipe to pager: %s", pager);
		return;
	}


	buf[BUFSIZ] = '\0';
	do {


		buf[0] = '\0';
		while ((fgets_ret = fgets(buf, BUFSIZ, stream)) != NULL &&
		       buf[0] == '#' && buf[1] == '#') {
		}


		if (fgets_ret == NULL) {
			fflush(cmd);
			break;
		}


	}  while (fprintf(cmd, "%s", buf) > 0);


	(void) pclose(cmd);
	fflush(stderr);
	fflush(stdout);
	fflush(stdin);
	return;
}
