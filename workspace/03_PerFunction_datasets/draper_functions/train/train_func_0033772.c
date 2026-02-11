ss_listen (int sci_idx)
{
    char *cp;
    ss_data *info;
    sigret_t (*sig_int)(int), (*old_sig_cont)(int);
    char input[BUFSIZ];
    sigset_t omask, igmask;
    int code;
    jmp_buf old_jmpb;
    ss_data *old_info = current_info;
    char *line;

    current_info = info = ss_info(sci_idx);
    sig_cont = (sigret_t (*)(int)) 0;
    info->abort = 0;
    sigemptyset(&igmask);
    sigaddset(&igmask, SIGINT);
    sigprocmask(SIG_BLOCK, &igmask, &omask);
    memcpy(old_jmpb, listen_jmpb, sizeof(jmp_buf));
    sig_int = signal(SIGINT, listen_int_handler);
    setjmp(listen_jmpb);
    sigprocmask(SIG_SETMASK, &omask, (sigset_t *) 0);

    while(!info->abort) {
	old_sig_cont = sig_cont;
	sig_cont = signal(SIGCONT, print_prompt);
	if (sig_cont == print_prompt)
	    sig_cont = old_sig_cont;
	if (info->readline) {
		line = (*info->readline)(current_info->prompt);
	} else {
		print_prompt(0);
		if (fgets(input, BUFSIZ, stdin) == input)
			line = input;
		else
			line = NULL;

		input[BUFSIZ-1] = 0;
	}
	if (line == NULL) {
		code = SS_ET_EOF;
		(void) signal(SIGCONT, sig_cont);
		goto egress;
	}

	cp = strchr(line, '\n');
	if (cp) {
	    *cp = '\0';
	    if (cp == line)
		continue;
	}
	(void) signal(SIGCONT, sig_cont);
	if (info->add_history)
		(*info->add_history)(line);

	code = ss_execute_line (sci_idx, line);
	if (code == SS_ET_COMMAND_NOT_FOUND) {
	    register char *c = line;
	    while (*c == ' ' || *c == '\t')
		c++;
	    cp = strchr (c, ' ');
	    if (cp)
		*cp = '\0';
	    cp = strchr (c, '\t');
	    if (cp)
		*cp = '\0';
	    ss_error (sci_idx, 0,
		    "Unknown request \"%s\".  Type \"?\" for a request list.",
		       c);
	}
	if (info->readline)
		free(line);
    }
    code = 0;
egress:
    (void) signal(SIGINT, sig_int);
    memcpy(listen_jmpb, old_jmpb, sizeof(jmp_buf));
    current_info = old_info;
    return code;
}
