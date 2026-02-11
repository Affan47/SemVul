h_expandall_option(opt, arg)

     char *opt;
     char *arg;
{
  if (noexpflg)
    errexit(34,NIL);
  expflg = TRUE;
  strcat (shapeflags, "-");
  strcat (shapeflags, opt);
  strcat (shapeflags, " ");
  return(0);
}
