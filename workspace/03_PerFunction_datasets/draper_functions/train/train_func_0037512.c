strtoupper(char *s)
{
  if(!s)
    return;

  while(*s)
    {
      *s = toupper(*s);
      s++;
    }
}
