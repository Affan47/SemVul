test_gtk_plugin_manager_configure_dialog (TestFixture *fixture)
{
  GtkTreeIter iter;
  GtkWidget *window;
  PeasPluginInfo *info;
  GList *list;
  GList *list_it;
  GtkWidget *content;
  GtkWidget *label = NULL;
  GtkWidget *button_box;
  GtkWidget *close_button = NULL;
  GtkWidget *help_button = NULL;

  info = peas_engine_get_plugin_info (fixture->engine, "configurable");

  peas_engine_load_plugin (fixture->engine, info);

  testing_get_iter_for_plugin_info (fixture->view, info, &iter);
  gtk_tree_selection_select_iter (fixture->selection, &iter);


  gtk_button_clicked (GTK_BUTTON (fixture->configure_button));

  window = find_window_by_title (GTK_WINDOW (fixture->window), "Configurable");
  g_assert (GTK_IS_DIALOG (window));

  content = gtk_dialog_get_content_area (GTK_DIALOG (window));
  list = gtk_container_get_children (GTK_CONTAINER (content));

  for (list_it = list; list_it != NULL; list_it = list_it->next)
    {
      if (GTK_IS_LABEL (list_it->data))
        {
          const gchar *text = gtk_label_get_text (GTK_LABEL (list_it->data));

          if (g_strcmp0 (text, "Hello, World!") == 0)
            label = GTK_WIDGET (list_it->data);
        }
    }

  g_assert (label != NULL);

  g_list_free (list);


  button_box = gtk_dialog_get_action_area (GTK_DIALOG (window));
  list = gtk_container_get_children (GTK_CONTAINER (button_box));

  for (list_it = list; list_it != NULL; list_it = list_it->next)
    {
      if (GTK_IS_BUTTON (list_it->data))
        {
          const gchar *text = gtk_button_get_label (GTK_BUTTON (list_it->data));

          if (g_strcmp0 (text, GTK_STOCK_CLOSE) == 0)
            close_button = GTK_WIDGET (list_it->data);
          else if (g_strcmp0 (text, GTK_STOCK_HELP) == 0)
            help_button = GTK_WIDGET (list_it->data);
        }
    }

  g_assert (close_button != NULL);
  g_assert (help_button != NULL);

  g_list_free (list);

  gtk_widget_destroy (window);
}
