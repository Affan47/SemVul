error_init (const char *gmsgid)
{
  char *ofwhat;


  error (gmsgid);
  ofwhat = print_spelling ((char *) alloca (spelling_length () + 1));
  if (*ofwhat)
    error ("(near initialization for %qs)", ofwhat);
}
