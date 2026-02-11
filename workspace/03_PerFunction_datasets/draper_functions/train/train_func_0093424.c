app_set_path(app_t *app, const char *value)
{
  g_assert(app != NULL && value != NULL);
  TRACE("%s", "");
  if (app->path)
    g_free(app->path);
  app->path = g_strdup(value);
  g_assert(app->path != NULL);
}
