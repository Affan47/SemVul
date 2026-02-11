localconfiguration_file_write(EasySpice *es)
{
  gchar *local_rcfile;

  if (getenv("HOME") != NULL) {
    local_rcfile=g_strdup_printf("%s/%s",getenv("HOME"), PROJECT_RCFILENAME);

    configuration_file_write_new(es, local_rcfile, TRUE);
    g_free(local_rcfile);
  }
}
