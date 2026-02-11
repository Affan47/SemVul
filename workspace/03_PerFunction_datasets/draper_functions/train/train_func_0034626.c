log_set_application_name(const char *name)
{
  tor_free(appname);
  appname = name ? tor_strdup(name) : NULL;
}
