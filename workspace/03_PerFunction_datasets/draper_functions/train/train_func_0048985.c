printremark(char *str)
{
	char *strtmp;
	int substrlen;
	char *substrend;
	char *strend;

	char *strbfr;


	strbfr = (char *) malloc(strlen((char *) str) + 1);
	if (!strbfr) {
		printf("No memory.\n");
		exit(-1);
	}


	strtmp = str;
	strend = &str[strlen(str)];


	while (strtmp < strend) {
		substrend = strchr(strtmp, '\n');
		substrlen = (substrend ? (substrend - strtmp) : strlen(strtmp));

		strncpy(strbfr, strtmp, substrlen);


		strbfr[substrlen] = (char) 0;

		printf("\\  %s\n", strbfr);

		strtmp = &strtmp[substrlen + (substrend ? 1 : 0)];

	}

	free(strbfr);
}
