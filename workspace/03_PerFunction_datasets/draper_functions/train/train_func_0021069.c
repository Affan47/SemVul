LigneSlash(char *pbuf)
{
  char *f;

  while(1)
  {
    if((f = fgets(pbuf,MAXL,pi)) != NULL)
    {
      if(*pbuf == '/') return 0;
    }
    else
      return 1;
  }
}
