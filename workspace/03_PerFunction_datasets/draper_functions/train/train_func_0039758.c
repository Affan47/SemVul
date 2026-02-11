another(int *pargc, char ***pargv, char *prompt)
{
	int len = strlen(line), ret;

	if (len >= sizeof(line) - 3) {
		printf("sorry, arguments too long\n");
		intr(0);
	}
	printf("(%s) ", prompt);
	line[len++] = ' ';
	if (fgets(&line[len], sizeof(line) - len, stdin) == NULL)
		intr(0);
	len += strlen(&line[len]);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	makeargv();
	ret = margc > *pargc;
	*pargc = margc;
	*pargv = margv;
	return (ret);
}
