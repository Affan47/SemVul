icodir_free(icodir_t *icodir)
{
  g_assert(icodir != NULL);
  g_assert(icodir->children == NULL);
  if (icodir->count_total != 0)
    ERR("path:%s, count_total:%d", icodir->path, icodir->count_total);

  if (icodir->path != NULL)
    g_free(icodir->path);
  if (icodir->parent != NULL)
    icodir->parent->children = g_list_remove(icodir->parent->children, icodir);
  g_free(icodir);
}
