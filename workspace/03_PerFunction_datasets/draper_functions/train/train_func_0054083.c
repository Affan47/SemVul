spinner_init (void)
{
  spinner_wanted = isatty (fileno (stdout));
  if (spinner_wanted == -1)
    abort ();

  if (!spinner_wanted)
    return;

  if (signal (SIGALRM, spinner_signal) == SIG_ERR)
    {
      printf ("(no spinner)\r");
      spinner_tick = 0;
      return;
    }
  alarm (1);


  setbuf (stdout, NULL);
}
