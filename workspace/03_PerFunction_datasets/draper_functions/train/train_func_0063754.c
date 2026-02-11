ico_list_find_icon(GList *icos, icodir_t *dir, char *ico_name)
{
  GList *hamster;
  ico_t  ico;

  g_assert(dir != NULL && ico_name != NULL);

  ico.dir = dir;
  ico.name = ico_name;
  hamster = g_list_find_custom(icos, &ico, (GCompareFunc)ico_compare_by_path);
  if (hamster == NULL)
    return NULL;
  return ((ico_t *)(hamster->data));
}
