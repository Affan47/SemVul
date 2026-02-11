launcher_button_release_event(GtkWidget *widget,
                                       GdkEventButton *event, launcher_t *l)
{
  guint  pos_x;
  guint  pos_y;
  gboolean launched;
  app_t *app;
  GtkWidget *dialog;
  apwalapp_t *apwal;

  g_assert(l != NULL);

  TRACE("type:%x, x:%f, y:%f, button:%d",
          event->type, event->x, event->y, event->button);

  if (event->button == 3)
  {
    if (!l->editor_started)
    {
      l->editor_started = TRUE;
      g_signal_handlers_disconnect_by_func(l->window, launcher_leave_notify_event, l);
      gtk_widget_hide(l->window);
      launcher_timeout_stop(l);
      while (gtk_events_pending())
      { gtk_main_iteration();
      }
      apwal = apwalapp_new();
    }
  }
  else
  {
    pos_x = (((int)event->x) / ICON_WIDTH) + app_list_min_x(l->apps);
    pos_y = (((int)event->y) / ICON_WIDTH) + app_list_min_y(l->apps);
    TRACE("EXEC x:%d, y:%d, pos_x:%d, pos_y:%d ",
            (int)event->x, (int)event->y, pos_x, pos_y);
    app = app_list_at_xy(l->apps, pos_x, pos_y);
    app_dumpln(app);
    launched = app_exec(app, l->apwal_pref->exit_at_app_launch);
    if (!launched)
    {
      dialog = gtk_message_dialog_new(GTK_WINDOW(l->window),
                 GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR,
                 GTK_BUTTONS_CLOSE, "An error occured while trying to launch "
                 "the application '%s'.\n(path:'%s')",
                 app->cmdline, app->path);
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_destroy(dialog);
    }
  }
  return TRUE;
}
