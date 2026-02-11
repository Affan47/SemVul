load_conf_modules(void)
{
  dlink_node *ptr = NULL;
  struct module_path *mpath = NULL;

  DLINK_FOREACH(ptr, conf_modules.head)
  {
    mpath = ptr->data;

    if (findmodule_byname(mpath->path) == NULL)
      load_one_module(mpath->path, 0);
  }
}
