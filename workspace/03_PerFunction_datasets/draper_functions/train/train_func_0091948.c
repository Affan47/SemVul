GenerateArraySpec2(char *iname, char *ispec, char *ospec, int olen)
#else
int GenerateArraySpec2(iname, ispec, ospec, olen)
     char *iname;
     char *ispec;
     char *ospec;
     int olen;
#endif
{

  char *buf;
  int len;
  int got=0;

  len = strlen(iname)+strlen(ispec)+2;
  buf = (char *)malloc(len);
  snprintf(buf, len, "%s %s", iname, ispec);
  if( *buf ){
    got = GenerateArraySpecification(buf, ospec, olen);
    free(buf);
  }
  return(got);
}
