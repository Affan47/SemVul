ladish_app_supervisor_dump(ladish_app_supervisor_handle supervisor_handle)
{
  struct list_head * node_ptr;
  struct ladish_app * app_ptr;
  char uuid_str[37];

  list_for_each(node_ptr, &supervisor_ptr->applist)
  {
    app_ptr = list_entry(node_ptr, struct ladish_app, siblings);
    uuid_unparse(app_ptr->uuid, uuid_str);
    log_info("app '%s' with commandline '%s'", app_ptr->name, app_ptr->commandline);
    log_info("  %s", uuid_str);
    log_info("  %s, %s, level '%s'", app_ptr->terminal ? "terminal" : "shell", app_ptr->autorun ? "autorun" : "stopped", app_ptr->level, app_ptr->commandline);
  }
}
