remove_app_internal(struct ladish_app_supervisor * supervisor_ptr, struct ladish_app * app_ptr)
{
  ASSERT(app_ptr->pid == 0);

  list_del(&app_ptr->siblings);

  supervisor_ptr->version++;

  cdbus_signal_emit(
    cdbus_g_dbus_connection,
    supervisor_ptr->opath,
    IFACE_APP_SUPERVISOR,
    "AppRemoved",
    "tt",
    &supervisor_ptr->version,
    &app_ptr->id);

  free(app_ptr->dbus_name);
  free(app_ptr->name);
  free(app_ptr->commandline);
  free(app_ptr->js_commandline);
  free(app_ptr);
}
