strip_termination(char *line)
{
  char *p;
  for (p=line; *p; p++) ;
  for (p--; isspace(*p); p--) *p='\0';
}
