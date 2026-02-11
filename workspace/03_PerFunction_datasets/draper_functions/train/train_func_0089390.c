SMTP_ok(int sock, char smtp_mode, int mintimeout)


{
    SIGHANDLERTYPE alrmsave;
    char reply[MSGBUFSIZE], *i;


    alrmsave = set_signal_handler(SIGALRM, null_signal_handler);
    set_timeout(mytimeout >= mintimeout ? mytimeout : mintimeout);

    smtp_response[0] = '\0';

    while ((SockRead(sock, reply, sizeof(reply)-1)) != -1)
    {
	size_t n;


	set_timeout(0);
	set_signal_handler(SIGALRM, alrmsave);

	n = strlen(reply);
	if (n > 0 && reply[n-1] == '\n')
	    reply[--n] = '\0';
	if (n > 0 && reply[n-1] == '\r')
	    reply[--n] = '\0';


	for (i = reply; *i; i++)
	    if (iscntrl((unsigned char)*i))
		*i = '?';

	if (outlevel >= O_MONITOR)
	    report(stdout, "%cMTP< %s\n", smtp_mode, reply);


	if (n < 3 || !strchr(" -", reply[3]))
	{
	    if (outlevel >= O_MONITOR)
		report(stderr, GT_("smtp listener protocol error\n"));
	    return SM_UNRECOVERABLE;
	}

	last_smtp_ok = time((time_t *) NULL);

	strlcat(smtp_response, reply,  sizeof(smtp_response));

	if (strchr("123", reply[0])
		&& isdigit((unsigned char)reply[1])
		&& isdigit((unsigned char)reply[2])
		&& strchr(" ", reply[3]))  {
	    return SM_OK;
	} else if (reply[3] != '-')
	    return SM_ERROR;

	strlcat(smtp_response, "\r\n", sizeof(smtp_response));


	set_signal_handler(SIGALRM, null_signal_handler);
	set_timeout(mytimeout);
    }


    set_timeout(0);
    set_signal_handler(SIGALRM, alrmsave);

    if (outlevel >= O_MONITOR)
	report(stderr, GT_("smtp listener protocol error\n"));
    return SM_UNRECOVERABLE;
}
