on_notebook_switch_page (GtkNotebook *notebook,
                         GtkWidget *page,
                         guint page_num,
                         GladeWindow *window)
{
  GladeWindowPrivate *priv = window->priv;
  GladeDesignView *view;
  GladeProject *project;
  GtkAction *action;
  gchar *action_name;

  view = GLADE_DESIGN_VIEW (gtk_notebook_get_nth_page (notebook, page_num));


  if (view == priv->active_view)
    return;

  window->priv->active_view = view;

  project = glade_design_view_get_project (view);

  refresh_title (window);

  set_sensitivity_according_to_project (window, project);


  gtk_notebook_set_current_page (priv->inspectors_notebook, page_num);
  gtk_notebook_set_current_page (priv->palettes_notebook, page_num);


  action_name = g_strdup_printf ("Tab_%d", page_num);
  action = gtk_action_group_get_action (priv->project_list_actiongroup,
                                        action_name);


  if (action != NULL)
    gtk_toggle_action_set_active (GTK_TOGGLE_ACTION (action), TRUE);

  g_free (action_name);

  refresh_undo_redo (window, project);


  project_selection_changed_cb (project, window);

  on_pointer_mode_changed (project, NULL, window);
}
