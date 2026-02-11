main()
{
	int len;
	char line[MAXLINE];
	int i;

	while ((len = getline2(line, MAXLINE)) != -1) {

		for (i = len - 1; i >= 0; i--) {
			if (line[i] != ' ' && line[i] != '\t') {
				if (i != (len - 1)) {
					line[i + 1] = '#';
					line[i + 2] = '\0';
				}
				break;
			}
			len--;
		}

		if (len > 0) {
			printf("%s", line);
		}
	}

	return 0;
}
