config_setup()
{
  FILE *cfile;
  char cbuf[1024];
  int got_file = 0;
  cfile = fopen(ROOT_CONFIG_FILE,"r");
  if (cfile)
    {
      nread_str(&config_user,cfile);
      fclose(cfile);
      got_file = 1;
    }
  if (getenv("HOME"))
    {
      snprintf(cbuf,sizeof(cbuf),"%s/%s",getenv("HOME"),USER_CONFIG_FILE);
      cfile = fopen(cbuf,"r");
      if (cfile)
	{
	  nread_str(&config_user,cfile);
	  fclose(cfile);
	  got_file = 1;
	}
    }
  if (!got_file)
    {
      fprintf(stderr,"Looked for config files at '%s' and '$HOME/%s', but could not find any. Quitting.\n",ROOT_CONFIG_FILE,USER_CONFIG_FILE);
      exit(EXIT_FAILURE);
    }
  datapath = cfgstr("datapath",0);
  if (!datapath)
    {
      fprintf(stderr,"Cannot find datapath in config files. Quitting.\n");
      exit(EXIT_FAILURE);
    }
  return 0;
}
