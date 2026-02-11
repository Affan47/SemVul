client_mechanism (Gsasl * ctx)
{
  static char mech[GSASL_MAX_MECHANISM_SIZE + 1] = "";
  char mechlist[BUFSIZ] = "";
  const char *suggestion;
  char *p;

  printf ("Enter list of server supported mechanisms, separate by SPC:\n");
  p = fgets (mechlist, sizeof (mechlist) - 1, stdin);
  if (p == NULL)
    {
      perror ("fgets");
      return NULL;
    }

  suggestion = gsasl_client_suggest_mechanism (ctx, mechlist);
  if (suggestion)
    printf ("Library suggests use of `%s'.\n", suggestion);

  printf ("Enter mechanism to use:\n");
  p = fgets (mech, sizeof (mech) - 1, stdin);
  if (p == NULL)
    {
      perror ("fgets");
      return NULL;
    }

  mech[strlen (mech) - 1] = '\0';

  return mech;
}
