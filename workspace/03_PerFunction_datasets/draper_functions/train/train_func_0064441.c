start_rsh_server (cvsroot_t *root, struct buffer **to_server_p,
                  struct buffer **from_server_p)
{


    char *cvs_rsh = (root->cvs_rsh != NULL
		     ? root->cvs_rsh : getenv ("CVS_RSH"));
    char *cvs_server = (root->cvs_server != NULL
			? root->cvs_server : getenv ("CVS_SERVER"));
    char *command;
    int tofd, fromfd;
    int child_pid;

    if (!cvs_rsh)
	cvs_rsh = RSH_DFLT;
    if (!cvs_server)
	cvs_server = "cvs";


    command = Xasprintf ("%s%s server", cvs_server, readonlyfs ? " -R" : "");

    {
	char argvport[16];
        char *argv[16];
	char **p = argv;

	*p++ = cvs_rsh;


	if (root->username != NULL)
	{
	    *p++ = "-l";
	    *p++ = root->username;
	}

	if (root->method == extssh_method && root->port)
	{
		snprintf(argvport, sizeof(argvport), "%d", root->port);
		*p++ = "-p";
		*p++ = argvport;
	}

	*p++ = root->hostname;
	*p++ = command;
	*p++ = NULL;

	if (trace)
        {
	    int i;

            fprintf (stderr, " -> Starting server: ");
	    for (i = 0; argv[i]; i++)
	        fprintf (stderr, "%s ", argv[i]);
	    putc ('\n', stderr);
	}
	child_pid = piped_child (argv, &tofd, &fromfd, true);

	if (child_pid < 0)
	    error (1, errno, "cannot start server via rsh");
    }
    free (command);

    make_bufs_from_fds (tofd, fromfd, child_pid, root, to_server_p,
                        from_server_p, 0);
}
