fm_tree_view_init (FMTreeView *view)
{
	view->details = g_new0 (FMTreeViewDetails, 1);

	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (view),
					GTK_POLICY_AUTOMATIC,
					GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_hadjustment (GTK_SCROLLED_WINDOW (view), NULL);
	gtk_scrolled_window_set_vadjustment (GTK_SCROLLED_WINDOW (view), NULL);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (view), GTK_SHADOW_IN);

	gtk_widget_show (GTK_WIDGET (view));

	g_signal_connect_object (view, "parent_set",
				 G_CALLBACK (parent_set_callback), view, 0);

	view->details->selection_location = NULL;

	view->details->selecting = FALSE;

    g_signal_connect_object (view->details->window,
                             "hidden-files-mode-changed",
                             G_CALLBACK (filtering_changed_callback),
                             view,
                             0);

	g_signal_connect_swapped (nemo_tree_sidebar_preferences,
				  "changed::" NEMO_PREFERENCES_TREE_SHOW_ONLY_DIRECTORIES,
				  G_CALLBACK (filtering_changed_callback), view);

	view->details->popup_file = NULL;

	view->details->clipboard_handler_id =
		g_signal_connect (nemo_clipboard_monitor_get (),
				  "clipboard_info",
				  G_CALLBACK (notify_clipboard_info), view);
}
