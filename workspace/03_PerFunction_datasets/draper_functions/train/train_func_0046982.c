hideProgressBar(struct TimerInfo_ *timer)
{
  DBG_fprintf(stderr, "Panel browser: scanning is finished, hiding progress bar.\n");

  g_source_remove(timer->timer);
  if (timer->label)
    {
      g_source_remove(timer->label);
      visu_ui_panel_browser_setMessage((const gchar*)0, GTK_MESSAGE_INFO);
    }
  if (timer->bt)
    gtk_widget_destroy(timer->bt);
}
