gog_graph_view_set_selection (GogGraphView *gview, GogObject *gobj)
{
	GogView *view;

	g_return_if_fail (GOG_IS_GRAPH_VIEW (gview));
	g_return_if_fail (GOG_IS_OBJECT (gobj));

	if (gview->selected_object == gobj)
		return;

	gview->selected_object = gobj;
	view = gog_view_find_child_view (GOG_VIEW (gview), gobj);

	if (gview->selected_view != view) {
		gview->selected_view = view;
		update_action (gview, NULL, 0, 0);
	}

	gog_view_queue_redraw (GOG_VIEW (gview));
	g_signal_emit (G_OBJECT (gview),
		       gog_graph_view_signals [GRAPH_VIEW_SELECTION_CHANGED],
		       0, gobj);
}
