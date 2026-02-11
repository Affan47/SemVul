dw_SetFilePositionNoRewind(FILE *f, char *id)
{
  char *buffer=(char*)NULL;
  int m, n;
  if ((n=(int)strlen(id)) > 0)
    {
      while (buffer=dw_ReadLine(f,buffer,&m))
	if (!memcmp(buffer,id,n))
	  {
	    dw_free(buffer);
	    return 1;
	  }
      if (buffer) dw_free(buffer);
    }
  return 0;
}
