ladish_app_supervisor_start_app(ladish_app_supervisor_handle supervisor_handle, ladish_app_handle app_handle)
{
  char uuid_str[37];
  char * js_dir;
  bool ret;

  app_ptr->zombie = false;

  ASSERT(app_ptr->pid == 0);

  if (strcmp(app_ptr->level, LADISH_APP_LEVEL_JACKSESSION) == 0)
  {
    uuid_unparse(app_ptr->uuid, uuid_str);
    js_dir = catdup4(supervisor_ptr->js_dir, "/", uuid_str, "/");
    if (js_dir == NULL)
    {
      log_error("catdup4() failed to compose app jack session dir");
      return false;
    }
  }
  else
  {
    js_dir = NULL;
  }

  ret = loader_execute(
    supervisor_ptr->name,
    supervisor_ptr->project_name,
    app_ptr->name,
    supervisor_ptr->dir != NULL ? supervisor_ptr->dir : "/",
    js_dir,
    app_ptr->terminal,
    app_ptr->commandline,
    &app_ptr->pid);

  free(js_dir);

  if (!ret)
  {
    return false;
  }

  ASSERT(app_ptr->pid != 0);
  app_ptr->state = LADISH_APP_STATE_STARTED;

  emit_app_state_changed(supervisor_ptr, app_ptr);
  return true;
}
