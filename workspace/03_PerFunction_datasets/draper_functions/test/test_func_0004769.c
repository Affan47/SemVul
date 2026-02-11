cmdscanner(int top)
{
    struct cmd *c;
    int l;

    if (!top)
	putchar('\n');
    for (;;) {
	if (fromatty) {
	    char *p;
	    if (lineedit)
		p = readline("ftp> ");
	    else
		p = simple_readline("ftp> ");
	    if(p == NULL) {
		printf("\n");
		quit(0, 0);
	    }
	    strlcpy(line, p, sizeof(line));
	    if (lineedit)
		add_history(p);
	    free(p);
	} else{
	    if (fgets(line, sizeof line, stdin) == NULL)
		quit(0, 0);
	}

	l = strlen(line);
	if (l == 0)
	    break;
	if (line[--l] == '\n') {
	    if (l == 0)
		break;
	    line[l] = '\0';
	} else if (l == sizeof(line) - 2) {
	    printf("sorry, input line too long\n");
	    while ((l = getchar()) != '\n' && l != EOF)
		;
	    break;
	}
	makeargv();
	if (margc == 0) {
	    continue;
	}
	c = getcmd(margv[0]);
	if (c == (struct cmd *)-1) {
	    printf("?Ambiguous command\n");
	    continue;
	}
	if (c == 0) {
	    printf("?Invalid command\n");
	    continue;
	}
	if (c->c_conn && !connected) {
	    printf("Not connected.\n");
	    continue;
	}
	(*c->c_handler)(margc, margv);
	if (bell && c->c_bell)
	    putchar('\007');
	if (c->c_handler != help)
	    break;
    }
    signal(SIGINT, intr);
    signal(SIGPIPE, lostpeer);
}
