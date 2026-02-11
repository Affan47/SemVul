mod_find_path(const char *path)
{
  dlink_node *ptr;
  struct module_path *mpath;

  DLINK_FOREACH(ptr, mod_paths.head)
  {
    mpath = ptr->data;

    if (!strcmp(path, mpath->path))
      return mpath;
  }

  return NULL;
}
