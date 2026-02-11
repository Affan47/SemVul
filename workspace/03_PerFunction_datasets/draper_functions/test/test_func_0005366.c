app_list_new(void)
{
  app_list_t *apps;
  apps = (app_list_t *) malloc(sizeof(app_list_t));
  g_assert(apps != NULL);
  apps->apps = NULL;
  apps->hamster = NULL;
  return apps;
}
