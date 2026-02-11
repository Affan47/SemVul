get_manpage_contents (char *pagename)
{
  static char *formatter_args[4] = { NULL };
  int pipes[2];
  pid_t child;
  RETSIGTYPE (*sigsave) (int signum);
  char *formatted_page = NULL;
  int arg_index = 1;

  if (formatter_args[0] == NULL)
    formatter_args[0] = find_man_formatter ();

  if (formatter_args[0] == NULL)
    return NULL;

  get_page_and_section (pagename);

  if (manpage_section)
    formatter_args[arg_index++] = manpage_section;
  else
    formatter_args[arg_index++] = "-a";

  formatter_args[arg_index++] = manpage_pagename;
  formatter_args[arg_index] = NULL;


#if PIPE_USE_FORK
  pipe (pipes);

  sigsave = signal (SIGCHLD, reap_children);

  child = fork ();
  if (child == -1)
    return NULL;

  if (child != 0)
    {


      close (pipes[1]);
      formatted_page = read_from_fd (pipes[0]);
      close (pipes[0]);
      signal (SIGCHLD, sigsave);
    }
  else
    {

      close (pipes[0]);
      freopen (NULL_DEVICE, "w", stderr);
      freopen (NULL_DEVICE, "r", stdin);
      dup2 (pipes[1], fileno (stdout));

      execv (formatter_args[0], formatter_args);


      close (pipes[1]);
      exit (EXIT_SUCCESS);
    }
#else

  {
    FILE *fpipe;
    char *cmdline;
    size_t cmdlen = 0;
    int save_stderr = dup (fileno (stderr));
    int fd_err = open (NULL_DEVICE, O_WRONLY, 0666);
    int i;

    for (i = 0; i < arg_index; i++)
      cmdlen += strlen (formatter_args[i]);


    cmdlen += 2 + 2 + 1;
    cmdline = xmalloc (cmdlen);

    if (fd_err > 2)
      dup2 (fd_err, fileno (stderr));
    sprintf (cmdline, "\"%s\" %s %s",
	     formatter_args[0], formatter_args[1], formatter_args[2]);
    fpipe = popen (cmdline, "r");
    free (cmdline);
    if (fd_err > 2)
      close (fd_err);
    dup2 (save_stderr, fileno (stderr));
    if (fpipe == 0)
      return NULL;
    formatted_page = read_from_fd (fileno (fpipe));
    if (pclose (fpipe) == -1)
      {
	if (formatted_page)
	  free (formatted_page);
	return NULL;
      }
  }
#endif


  if (formatted_page)
    clean_manpage (formatted_page);

  return formatted_page;
}
