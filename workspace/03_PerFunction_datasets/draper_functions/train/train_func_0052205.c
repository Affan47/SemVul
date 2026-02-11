esd_config_read(void)
{
  FILE *fh;
  char *fn;
  const char *tmpenv;

  if(read_esd_config) return;

  fn = malloc(sizeof(SYSCONFDIR) + sizeof("/esd.conf"));
  strcpy(fn, SYSCONFDIR "/esd.conf");
  fh = fopen(fn, "r");
  if(fh)
    {
      esd_config_read_file(fh);
      fclose(fh);
    }
  free(fn);

  tmpenv = getenv("HOME");
  if(tmpenv) {
    fn = malloc(strlen(tmpenv) + sizeof("/.esd.conf"));
    sprintf(fn, "%s/.esd.conf", tmpenv);

    fh = fopen(fn, "r");

    if(fh)
      {
	esd_config_read_file(fh);
	fclose(fh);
      }

    free(fn);
  }

  tmpenv=getenv("ESD_NO_SPAWN");
  if(tmpenv)
    esd_no_spawn=1;

  tmpenv = getenv("ESD_SPAWN_OPTIONS");
  if(tmpenv && strlen(tmpenv) < (sizeof(esd_spawn_options) - 1))
    strcpy(esd_spawn_options, tmpenv);

  tmpenv = getenv("ESD_DEFAULT_OPTIONS");
  if(tmpenv && strlen(tmpenv) < (sizeof(esd_default_options) - 1))
    strcpy(esd_default_options, tmpenv);

  read_esd_config = 1;
}
