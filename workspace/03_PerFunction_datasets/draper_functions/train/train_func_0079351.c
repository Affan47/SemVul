doinput ()
{
  register int cc;
  char ibuf[BUFSIZ];

  while ((cc = read (0, ibuf, BUFSIZ)) > 0)
    (void) write (master, ibuf, cc);
  done ();
}
