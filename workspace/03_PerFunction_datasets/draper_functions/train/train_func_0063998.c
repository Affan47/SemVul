nowhite_strcmp(char *s,char *t)
{
  char *p;

  while (iswhite(*s)) s++;
  while (iswhite(*t)) t++;
  if ((*s==0)||(*t==0)) return strcmp(s,t);
  p=s+strlen(s)-1;
  while (iswhite(*p)) *(p--)=0;
  p=t+strlen(t)-1;
  while (iswhite(*p)) *(p--)=0;
  return strcmp(s,t);
}
