trim(char * str)
{
  int i=0,j=0;

  if (str==0) return;
  if (strlen(str)==0) return;

  while ((str[i]==' ') || (str[i]=='"')) i++;
  if (i!=0) {
    for (j=0;j<strlen(str)-i;j++) {
      str[j]=str[i+j];
    }
    str[j]=0;
  }
  i=strlen(str)-1;
  while ((i>1) && ((str[i]==' ') || (str[i]=='"') ||
                   (str[i]==10) || (str[i]==13))) i--;
  if (i!=strlen(str)-1) {
    str[i+1]=0;
  }
}
