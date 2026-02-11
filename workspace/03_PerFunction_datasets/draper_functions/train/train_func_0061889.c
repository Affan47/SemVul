chain_open (int stdin_fd, tCC** pp_args, pid_t* p_child)
{
  t_fd_pair stdout_pair;
  pid_t ch_id;
  tCC *pz_cmd;

  stdout_pair.read_fd = stdout_pair.write_fd = -1;


  if (pipe ((int *) &stdout_pair) < 0)
    {
      if (p_child != (pid_t *) NULL)
        *p_child = NOPROCESS;
      return -1;
    }


  if (pp_args == (tCC **) NULL)
    pp_args = def_args;


  if (pz_cmd = *pp_args,
      (pz_cmd == (char *) NULL) || (*pz_cmd == '\0'))
    {

      pz_cmd = getenv ("SHELL");
      if (pz_cmd == (char *) NULL)
        pz_cmd = "sh";
    }

#ifdef DEBUG_PRINT
  printf ("START:  %s\n", pz_cmd);
  {
    int idx = 0;

    while (pp_args[++idx] != (char *) NULL)
      printf ("  ARG %2d:  %s\n", idx, pp_args[idx]);
  }
#endif


  ch_id = fork ();
  switch (ch_id)
    {
    case NOPROCESS:
      close (stdout_pair.read_fd);
      close (stdout_pair.write_fd);
      if (p_child != (pid_t *) NULL)
        *p_child = NOPROCESS;
      return -1;

    default:
      if (p_child != (pid_t *) NULL)
        *p_child = ch_id;
#ifdef DEBUG_PRINT
      printf ("for pid %d:  stdin from %d, stdout to %d\n"
              "for parent:  read from %d\n",
              ch_id, stdin_fd, stdout_pair.write_fd, stdout_pair.read_fd);
#endif
      close (stdin_fd);
      close (stdout_pair.write_fd);
      return stdout_pair.read_fd;

    case NULLPROCESS:
      break;
    }


  close (stdout_pair.read_fd);


  close (STDIN_FILENO);
  close (STDOUT_FILENO);


  dup2 (stdout_pair.write_fd, STDOUT_FILENO);
  dup2 (stdin_fd, STDIN_FILENO);

  if (*pp_args == (char *) NULL)
    *pp_args = pz_cmd;

  execvp (pz_cmd, (char**)pp_args);
  fprintf (stderr, "Error %d:  Could not execvp( '%s', ... ):  %s\n",
           errno, pz_cmd, xstrerror (errno));
  exit (EXIT_PANIC);
}
