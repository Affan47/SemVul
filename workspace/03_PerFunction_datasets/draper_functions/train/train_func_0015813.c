opt_welldefined (char *ep)
{
  if ((strcmp (ep, "USER") == 0) ||
      (strcmp (ep, "DISPLAY") == 0) ||
      (strcmp (ep, "PRINTER") == 0) ||
      (strcmp (ep, "SYSTEMTYPE") == 0) ||
      (strcmp (ep, "JOB") == 0) || (strcmp (ep, "ACCT") == 0))
    return (1);
  return (0);
}
