dump_string (char *s)
{
  if ((s == NULL) || (strlen (s) == 0))
    fprintf (stdout, "(null)\n");
  else
    fprintf (stdout, ">>%s<<\n", s);
}
