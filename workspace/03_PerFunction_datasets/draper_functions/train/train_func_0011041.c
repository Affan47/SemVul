do_list(char *args)
{
    FILE	*fp = NULL;
    int		c, prev;

    if (!args || strcmp(args, "active") == 0) {
	if (!active) {
	    printf(CODE_TO_STR(NNTP_ERR_FAULT)
		   " Active file not available.\r\n");
	    return;
	}

	fp = fopen(active, "r");
	if (fp)
	    printf(CODE_TO_STR(NNTP_OK_GROUPS) " Active file follows.\r\n");
	else
	    perror(active);
    } else if (strcmp(args, "newsgroups") == 0) {
	if (!newsgroups) {
	    printf(CODE_TO_STR(NNTP_ERR_FAULT)
		   " Newsgroups file not available.\r\n");
	    return;
	}

	fp = fopen(newsgroups, "r");
	if (fp)
	    printf(CODE_TO_STR(NNTP_OK_GROUPS) " Descriptions follow.\r\n");
	else
	    perror(newsgroups);
    } else {
	printf(CODE_TO_STR(NNTP_ERR_CMDSYN) " Syntax error.\r\n");
	return;
    }


    if (!fp) {
	printf(CODE_TO_STR(NNTP_ERR_FAULT) " Couldn't open file.\r\n");
	return;
    }

    prev = 0;
    while ((c = getc(fp)) != EOF) {
	prev = c;
	if (c == '\n')
	    putchar('\r');
	putchar(c);
    }

    if (prev == '\n')
	printf(".\r\n");
    else
	printf("\r\n.\r\n");

    fclose(fp);
}
