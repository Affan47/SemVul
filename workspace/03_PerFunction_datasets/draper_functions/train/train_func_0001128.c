mod_clear_paths(void)
{
  struct module_path *pathst;
  dlink_node *ptr;
  dlink_node *next_ptr;

  DLINK_FOREACH_SAFE(ptr, next_ptr, mod_paths.head)
  {
    pathst = ptr->data;

    dlinkDelete(&pathst->node, &mod_paths);
    MyFree(pathst);
  }

  DLINK_FOREACH_SAFE(ptr, next_ptr, conf_modules.head)
  {
    pathst = ptr->data;

    dlinkDelete(&pathst->node, &conf_modules);
    MyFree(pathst);
  }
}
