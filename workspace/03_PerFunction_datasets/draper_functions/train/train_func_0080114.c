gdu_application_local_command_line (GApplication    *_app,
                                    gchar         ***arguments,
                                    int             *exit_status)
{
  GduApplication *app = GDU_APPLICATION (_app);


  if (g_strcmp0 ((*arguments)[0], "./gnome-disks") == 0)
    app->running_from_source_tree = TRUE;


  return G_APPLICATION_CLASS (gdu_application_parent_class)->local_command_line (_app,
                                                                                 arguments,
                                                                                 exit_status);
}
