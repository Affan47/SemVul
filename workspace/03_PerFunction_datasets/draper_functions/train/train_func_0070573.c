fbl_stostr(str)

char *str;

  {
  char *resstr;
  long   i;
  long   j=0;

  resstr = (char *)mbkalloc(100);
  resstr[0] = '\0';

  for ( i=1;str[i+1]!='\0';i++)
    {
    resstr[j++]=str[i];
    if ((str[i]==str[0])&&(str[i+1]==str[0]))
      i++;
    }

  return( &resstr[0] );
  }
