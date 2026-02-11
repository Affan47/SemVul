error(const char *message)
{
  if (verbosity>0 && vdots>0)
    fprintf(stdout,"\n");
  if (verbosity>0)
    fprintf(stdout,"SVQP2 error: %s\n", message);
  errmsg = message;
  return -1;
}
