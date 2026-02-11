verror (msg, args)
     char *msg;
     va_list args;
{
  int i;
  FILE_BUF *ip = NULL;

  print_containing_files ();

  for (i = indepth; i >= 0; i--)
    if (instack[i].fname != NULL) {
      ip = &instack[i];
      break;
    }

  if (ip != NULL)
    fprintf (stderr, "%s:%d: ", ip->nominal_fname, ip->lineno);
  vfprintf (stderr, msg, args);
  fprintf (stderr, "\n");
  errors++;
}
