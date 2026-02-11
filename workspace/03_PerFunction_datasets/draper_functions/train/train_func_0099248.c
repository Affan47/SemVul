pipe_mkisofs_up (char *mkisofs_argv[],int infd,int outfd,off64_t outoff)
{ pid_t mkisofs_pid;
  int   fildes[2],ret,n;

    if (pipe (fildes) < 0)
        perror (":-( unable to create pipe"), exit(FATAL_START(errno));

    if ((mkisofs_pid=fork ()) == (pid_t)-1)
	perror (":-( unable to fork genisoimage"), exit(FATAL_START(errno));
    else if (mkisofs_pid == 0)
    {	dup2  (fildes[1],1);
	close (fildes[0]);
	close (fildes[1]);
	close (outfd);

	if (next_session)
	{
#ifdef PASS_STDIN_TO_MKISOFS
	    dup2(infd,0);
	    close(infd);
	    infd=0;
#endif
	    if ((n=fcntl (infd,F_GETFD))<0) n=0;
	    fcntl (infd,F_SETFD,n&~FD_CLOEXEC);
	}
	else
	    close (infd);


	setuid(getuid());
	execvp (mkisofs_argv[0],mkisofs_argv);
	fprintf (stderr,":-( unable to execute %s: ",mkisofs_argv[0]),
	perror (NULL), exit (FATAL_START(errno));
    }

    close (fildes[1]);

    n=builtin_dd(fildes[0],outfd,outoff);

    if (n==0)
    {	if ((waitpid (mkisofs_pid,&ret,0)) == -1)
	    perror (":-( waitpid failed"), exit (errno);

	if (!WIFEXITED(ret) || WEXITSTATUS(ret)!=0)
	    fprintf (stderr,":-( %s has failed: %d\n",mkisofs_argv[0],WEXITSTATUS(ret)),
	    exit (errno=WIFEXITED(ret)?WEXITSTATUS(ret):255);
    }
    else if (n<0)
    { int err = errno;
	errno = err&FATAL_MASK;
	perror (":-( write failed"), exit (err);
    }
}
