safe_exit (void)
{
  static int doing_exit = 0;

  if (! doing_exit)
    {
      doing_exit = 1;
      client_exit ();
      exit (1);
    }
}
