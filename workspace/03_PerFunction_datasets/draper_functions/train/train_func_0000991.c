terminaltypeok (char *s)
{
#ifdef HAVE_TGETENT
  char buf[2048];

  if (terminaltype == NULL)
    return 1;

  if (tgetent (buf, s) == 0)
    return 0;
#endif

  return 1;
}
