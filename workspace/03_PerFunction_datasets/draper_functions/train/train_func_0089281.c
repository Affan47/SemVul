eel_gtk_tree_view_set_activate_on_single_click (GtkTreeView *tree_view,
						gboolean should_activate)
{
	guint button_press_id;

	button_press_id = GPOINTER_TO_UINT
		(g_object_get_data (G_OBJECT (tree_view),
				    "eel-tree-view-activate"));

	if (button_press_id && !should_activate) {
		g_signal_handler_disconnect (tree_view, button_press_id);
		g_object_set_data (G_OBJECT (tree_view),
				   "eel-tree-view-activate",
				   NULL);
	} else if (!button_press_id && should_activate) {
		button_press_id = g_signal_connect
			(tree_view,
			 "button_press_event",
			 G_CALLBACK  (tree_view_button_press_callback),
			 NULL);
		g_object_set_data (G_OBJECT (tree_view),
				   "eel-tree-view-activate",
				   GUINT_TO_POINTER (button_press_id));
	}
}
