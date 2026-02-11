read_cache_file(char *file, time_t *date, char **ipaddr)
{
  FILE *fp = NULL;
  char buf[BUFSIZ+1];
  char *p;
  char *datestr;
  char *ipstr;
#if HAVE_STAT
  struct stat st;
#endif


  buf[BUFSIZ] = '\0';


  *date = 0;
  *ipaddr = NULL;

#if HAVE_STAT
  if(stat(file, &st) != 0)
  {
    if(errno == ENOENT)
    {
      return(0);
    }
    return(-1);
  }
#endif

  if((fp=fopen(file, "r")) == NULL)
  {
    return(-1);
  }

  if(fgets(buf, BUFSIZ, fp) != NULL)
  {


    p = buf;
    while(*p != '\0' && *p != '\r' && *p != '\n') { p++; }
    *p = '\0';


    p = buf;
    while(*p != '\0' && *p != ',') { p++; }
    if(*p == '\0')
    {
      fprintf(stderr, "malformed cache file\n");
      goto ERR;
    }


    *p++ = '\0';

    datestr = buf;
    ipstr = p;

    *date = strtoul(datestr, NULL, 10);

    if (strcmp(ipstr,"(null)")!=0)
      *ipaddr = strdup(ipstr);
  }
  else
  {
    *date = 0;
    *ipaddr = NULL;
  }

  fclose(fp);

  return 0;

ERR:

  if(fp) { fclose(fp); }
  return(-1);
}
