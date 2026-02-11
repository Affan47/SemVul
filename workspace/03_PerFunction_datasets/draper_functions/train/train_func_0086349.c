strsigno (int signo)
{
  const char *name;
  static char buf[32];

  if (signal_names == NULL)
    {
      init_signal_tables ();
    }

  if ((signo < 0) || (signo >= num_signal_names))
    {

      name = NULL;
    }
  else if ((signal_names == NULL) || (signal_names[signo] == NULL))
    {

      sprintf (buf, "Signal %d", signo);
      name = (const char *) buf;
    }
  else
    {

      name = signal_names[signo];
    }

  return (name);
}
