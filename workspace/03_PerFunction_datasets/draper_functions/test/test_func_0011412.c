icodir_list_find_with_parent(GList *dirs, icodir_t *parentdir)
{
  icodir_t *dir;
  GList    *hamster;
  g_assert(parentdir != NULL);
  TRACE("dir:%p", parentdir);
  hamster = g_list_first(dirs);
  while (hamster != NULL)
  {
    dir = hamster->data;
    if (dir == parentdir)
      break;
    hamster = g_list_next(hamster);
  }
  return hamster;
}
