icon_list_remove(icon_list_t *icons, char *dirname)
{
  icodir_t *dir;
  g_assert(icons != NULL && dirname != NULL);

  TRACE("'%s'", dirname);

  dir = icodir_list_find(icons->dirs, dirname);
  if (dir == NULL)
    ERR("dirname:%s not exist", dirname);

  if (dir->recursive == TRUE)
    icon_list_remove_children(icons, dir);
  ico_list_remove(&icons->icos, dir, icons);
  icons->dirs = g_list_remove(icons->dirs, dir);
  icodir_free(dir);
}
