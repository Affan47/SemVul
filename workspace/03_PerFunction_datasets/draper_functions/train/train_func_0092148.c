on_notebook_tab_removed (GtkNotebook     *notebook,
                         GladeDesignView *view,
                         guint            page_num,
                         GladeWindow     *window)
{
  GladeWindowPrivate *priv = window->priv;
  GladeProject *project;

  --priv->num_tabs;

  if (priv->num_tabs == 0)
    {
      gtk_widget_hide (GTK_WIDGET (priv->editor));
      priv->active_view = NULL;
    }

  project = glade_design_view_get_project (view);

  g_signal_handlers_disconnect_by_func (project, project_notify_handler_cb, window);
  g_signal_handlers_disconnect_by_func (project, project_selection_changed_cb, window);
  g_signal_handlers_disconnect_by_func (project, project_targets_changed_cb, window);
  g_signal_handlers_disconnect_by_func (project, project_changed_cb, window);
  g_signal_handlers_disconnect_by_func (project, on_pointer_mode_changed, window);

  gtk_notebook_remove_page (priv->inspectors_notebook, page_num);
  gtk_notebook_remove_page (priv->palettes_notebook, page_num);

  clean_actions (window);


  project_selection_changed_cb (project, window);

  on_pointer_mode_changed (project, NULL, window);


  glade_app_remove_project (project);

  refresh_projects_list_menu (window);

  refresh_title (window);

  if (priv->active_view)
    set_sensitivity_according_to_project (window,
                                          glade_design_view_get_project
                                          (priv->active_view));
  else
    gtk_action_group_set_sensitive (priv->project_actiongroup, FALSE);

}
