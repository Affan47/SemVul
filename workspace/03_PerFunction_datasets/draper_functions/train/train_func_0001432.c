alarm_list_window_rows_reordered (GtkTreeModel *model,
                                  GtkTreePath  *path,
                                  GtkTreeIter  *iter,
                                  gpointer      arg3,
                                  gpointer      data)
{
    AlarmApplet *applet = (AlarmApplet *)data;
    AlarmListWindow *list_window = applet->list_window;


    if (!list_window)
        return;


    list_window->reordered = TRUE;
}
