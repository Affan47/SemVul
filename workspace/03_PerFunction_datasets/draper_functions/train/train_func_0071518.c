app_list_length(app_list_t *apps)
{
  g_assert(apps != NULL && apps->apps != NULL);

  return g_list_length(apps->apps);
}
