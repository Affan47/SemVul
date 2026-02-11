str_ncopy(char *string1,char *string2,int len)
{ int i;
  char ch;

  for (i=0;i<len;i++)
  { ch=string2[i];
    string1[i]=ch;
    if (!ch) break; }
  string1[i]=0; }
