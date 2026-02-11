cgi_nonblank(string)
     char *string;
{
  char *ptr;

  for(ptr=string; *ptr; ptr++)
    if (isgraph((int)(*ptr))) return(1);

  return(0);
}
