pipe_sendmail(const char *to)
{
  cups_file_t	*fp;
  int		pid;
  int		pipefds[2];
  int		argc;
  char		*argv[100],
		line[1024],
		*lineptr;


  strlcpy(line, mailtoSendmail, sizeof(line));
  argv[0] = line;
  argc    = 1;

  for (lineptr = strchr(line, ' '); lineptr; lineptr = strchr(lineptr, ' '))
  {
    while (*lineptr == ' ')
      *lineptr++ = '\0';

    if (*lineptr)
    {


      argv[argc ++] = lineptr;


      if (argc >= (int)(sizeof(argv) / sizeof(argv[0]) - 2))
        break;
    }
  }

  argv[argc ++] = (char *)to;
  argv[argc]    = NULL;


  if (pipe(pipefds))
  {
    perror("ERROR: Unable to create pipe");
    return (NULL);
  }


  if ((pid = fork()) == 0)
  {


    close(0);
    dup(pipefds[0]);

    close(1);
    dup(2);

    close(pipefds[0]);
    close(pipefds[1]);

    execvp(argv[0], argv);
    exit(errno);
  }
  else if (pid < 0)
  {


    perror("ERROR: Unable to fork command");

    close(pipefds[0]);
    close(pipefds[1]);

    return (NULL);
  }


  close(pipefds[0]);

  if ((fp = cupsFileOpenFd(pipefds[1], "w")) == NULL)
  {
    int	status;


    close(pipefds[1]);
    wait(&status);
  }

  return (fp);
}
