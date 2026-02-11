ChopLocaleComponents(char *path,const unsigned long components)
{
  long
    count;

  register char
    *p;

  if (*path == '\0')
    return;
  p=path+strlen(path)-1;
  if (*p == '/')
    *p='\0';
  for (count=0; (count < (long) components) && (p > path); p--)
    if (*p == '/')
      {
        *p='\0';
        count++;
      }
}
