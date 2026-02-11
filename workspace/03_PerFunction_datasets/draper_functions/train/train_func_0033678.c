update_pidfile (char *pidfile)
{
  long p;
  pid_t pid;
  mode_t prev_umask;
  FILE *file;


  file = fopen (pidfile, "r");
  if (file)
    {
      if (fscanf(file, "%ld", &p) == 1 && (pid = p) &&
          (getpgid (pid) > -1))
        {
          err_msg("daemon already running: %s pid %ld\n", pidfile, p);
          exit (1);
        }
      fclose (file);
    }


  prev_umask = umask (0112);
  unlink(pidfile);

  file = fopen (pidfile, "w");
  if (!file)
    {
      err_msg("Error writing pidfile '%s' -- %s\n",
               pidfile, strerror (errno));
      exit (1);
    }
  fprintf (file, "%ld\n", (long) getpid());
  fclose (file);
  umask (prev_umask);
}
