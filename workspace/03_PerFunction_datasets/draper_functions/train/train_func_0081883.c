cb_search_popup_insert_pressed(GtkWidget *widget, gpointer pt)
{
	GMedialib        *gml = (GMedialib *)pt;
	gint              pos = gml_pl_get_selected_pos(gml);
	GtkTreeSelection *sel;

	if (pos != -1) {
		sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(gml->search.list_results));
		gtk_tree_selection_selected_foreach(sel, insert_selected_foreach_func,
		                                    (gpointer)gml);
	}


}
