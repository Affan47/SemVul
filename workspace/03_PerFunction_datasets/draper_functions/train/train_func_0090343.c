gui_dialog_detach(struct gui_dialog* dlg)
{
  gint n;
  GtkWidget *window, *notebook;
  gulong handler_id;

  if (dlg->type != GUI_DIALOG_TAB) {
    return;
  }
  dlg->type = GUI_DIALOG_WINDOW;


  g_object_ref(dlg->vbox);


  notebook = dlg->v.tab.notebook;
  handler_id = dlg->v.tab.handler_id;
  g_signal_handler_disconnect(notebook, handler_id);

  n = gtk_notebook_page_num(GTK_NOTEBOOK(dlg->v.tab.notebook), dlg->vbox);
  gtk_notebook_remove_page(GTK_NOTEBOOK(dlg->v.tab.notebook), n);


  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), dlg->title);
  setup_dialog(window, toplevel);

  gtk_container_add(GTK_CONTAINER(window), dlg->vbox);
  dlg->v.window = window;
  g_signal_connect(window, "delete_event",
    G_CALLBACK(gui_dialog_delete_handler), dlg);

  gtk_window_set_default_size(GTK_WINDOW(dlg->v.window),
                              dlg->default_width,
			      dlg->default_height);
  gtk_widget_show_all(window);
}
