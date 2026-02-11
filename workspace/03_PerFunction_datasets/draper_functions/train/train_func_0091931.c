endgame_report_init(struct endgame_report *preport)
{
  GtkWidget *sw, *view;

  fc_assert_ret(NULL != preport);

  gui_dialog_new(&preport->shell, GTK_NOTEBOOK(top_notebook), NULL, TRUE);
  gui_dialog_set_title(preport->shell, _("Score"));

  gui_dialog_set_default_size(preport->shell, 700, 420);


  sw = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),
                                      GTK_SHADOW_ETCHED_IN);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  gtk_container_add(GTK_CONTAINER(preport->shell->vbox), sw);

  view = gtk_tree_view_new();
  gtk_widget_set_name(view, "small_font");
  gtk_container_add(GTK_CONTAINER(sw), view);
  preport->tree_view = GTK_TREE_VIEW(view);

  if (preport->shell->type == GUI_DIALOG_TAB) {
    gtk_widget_set_hexpand(GTK_WIDGET(view), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(view), TRUE);
  }

  gui_dialog_show_all(preport->shell);
}
