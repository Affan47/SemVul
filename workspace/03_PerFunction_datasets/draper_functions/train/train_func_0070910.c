to_lower(char * str)
{
  int i;
  if (str==0) return;
  for (i=0;i<strlen(str);i++) {
    str[i] = tolower(str[i]);
  }
}
