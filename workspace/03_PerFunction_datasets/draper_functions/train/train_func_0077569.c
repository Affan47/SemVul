print_error (char *error, int critical)
{
#ifdef DEBUG
  printf ("print_error\n");
#endif

  fprintf (stderr, "keylaunch: %s", error);
  if (critical)
    exit (1);
}
