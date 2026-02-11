log_addlogging_file(const char *filename,int loglevel)
{
  FILE *fp;
  fp=fopen(filename,"a");
  if (fp==NULL)
  {
    log_log(LOG_ERR,"cannot open logfile (%s) for appending: %s",filename,strerror(errno));
    exit(1);
  }
  log_addlogging_fp(fp,loglevel);
}
