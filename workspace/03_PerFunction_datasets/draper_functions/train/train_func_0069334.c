egg_tree_multi_drag_motion_event (GtkWidget      *widget,
				  GdkEventMotion *event,
				  gpointer        data)
{
  EggTreeMultiDndData *priv_data;

  priv_data = g_object_get_data (G_OBJECT (widget), EGG_TREE_MULTI_DND_STRING);

  if (gtk_drag_check_threshold (widget,
				priv_data->x,
				priv_data->y,
				event->x,
				event->y))
    {
      GList *path_list = NULL;
      GtkTreeSelection *selection;
      GtkTreeModel *model;
      GdkDragContext *context;
      TreeViewDragInfo *di;

      di = get_info (GTK_TREE_VIEW (widget));

      if (di == NULL)
	return FALSE;

      selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (widget));
      if (priv_data->motion_notify_handler) {
        g_signal_handler_disconnect (widget, priv_data->motion_notify_handler);
        priv_data->motion_notify_handler = 0;
      }
      if (priv_data->button_release_handler) {
        g_signal_handler_disconnect (widget, priv_data->button_release_handler);
        priv_data->button_release_handler = 0;
      }
      stop_drag_check (widget);
      gtk_tree_selection_selected_foreach (selection, selection_foreach, &path_list);
      path_list = g_list_reverse (path_list);
      model = gtk_tree_view_get_model (GTK_TREE_VIEW (widget));
      if (egg_tree_multi_drag_source_row_draggable (EGG_TREE_MULTI_DRAG_SOURCE (model), path_list))
	{
	  gulong sig;


	  sig = g_signal_connect (widget,
	                          "drag-begin",
	                          G_CALLBACK (egg_tree_multi_drag_begin),
	                          NULL);
	  context = gtk_drag_begin (widget,
				    gtk_drag_source_get_target_list (widget),
				    di->source_actions,
	                            priv_data->pressed_button,
				    (GdkEvent*)event);
	  g_signal_handler_disconnect (widget, sig);
	  set_context_data (context, path_list);
	}
      else
	{
	  path_list_free (path_list);
	}
    }
  return TRUE;
}
