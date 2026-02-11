gml_pl_get_selected_pos(GMedialib *gml)
{
	GtkTreeSelection *selection;
	gint              pos = -1;

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(gml->playlist.list));


	if (gtk_tree_selection_count_selected_rows(selection) == 1) {
		gtk_tree_selection_selected_foreach(selection, view_selected_foreach_func, &pos);
	}
	return pos;
}
