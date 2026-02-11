close_input (void)
{
  int status;

  fclose (fin);

  if (waitpid (cpp_pid, &status, 0) < 0)
    {
      perror ("waitpid");
      crash ();
    }
  if (WIFSIGNALED (status) || WEXITSTATUS (status) != 0)
    {
      if (WIFSIGNALED (status))
	fprintf (stderr, _("%s: C preprocessor failed with signal %d\n"),
		 cmdname, WTERMSIG (status));
      else
	fprintf (stderr, _("%s: C preprocessor failed with exit code %d\n"),
		 cmdname, WEXITSTATUS (status));
      crash ();
    }
}
