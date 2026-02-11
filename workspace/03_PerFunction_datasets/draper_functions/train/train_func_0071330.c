getRemprogByName(void)
{
  FILE *fp;
  int len, ret;
  register int i;

  if (domain == (char *)(0))
(void)yp_get_default_domain(&domain);

  if (_remprogBuffer != (char *)0) free(_remprogBuffer);
  _remprogBuffer = (char *)(0);
  if (_remprogEntries != (Remprog *)0) delete [] _remprogEntries;
  _remprogEntries=(Remprog *)0;

  ret = yp_match(domain, map, (char *)serviceName().string(), strlen((char *)serviceName().string()), &_remprogBuffer, &len);
  switch(ret)
   {
   case YPERR_BADARGS:
   case YPERR_MAP:
   case YPERR_KEY:
   case YPERR_NOMORE:
   case YPERR_ACCESS:
     return(ret);
   case 0:
   {
     int retval=remprogParseValue(_remprogBuffer);
     return retval;
   }
   }


  if ((fp = fopen(file, "r")) == (FILE *)(0)) return(ret);
  char buf[128];
  while (fgets(buf, sizeof(buf), fp) == buf)
   {
     for (i = 0; buf[i] != 0; i++)
      {
        if(isspace(buf[i]))  break;
      }

     buf[i] = 0;
     if (strcmp((char *)buf, (char *)serviceName().string())==0)
      {
        (void)fclose(fp);
        return(remprogParseValue(&buf[i+1]));
      }
   }
  (void)fclose(fp);
  return(ret);
}
