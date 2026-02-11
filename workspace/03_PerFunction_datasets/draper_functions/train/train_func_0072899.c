confdir(void)
{
  static char *confdirvar = NULL;

	if (confdirvar == NULL && (confdirvar = getenv(CONFDIR_VAR)) == NULL)
    confdirvar = I4LCONFDIR;

  return(confdirvar);
}
