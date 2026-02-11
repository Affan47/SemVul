tree_selection_collect_data(GtkTreeSelection *selection,
	tree_selection_get_data_func gdf, GCompareFunc cfn)
{
	collect_data_struct_t cdata;

    g_assert(NULL != selection);

	cdata.results = NULL;
	cdata.to_unselect = NULL;
	cdata.cfn = cfn;
	cdata.gdf = gdf;
	cdata.tv = gtk_tree_selection_get_tree_view(selection);
	if (GUI_PROPERTY(gui_debug) >= 3) {
		cdata.name = gtk_widget_get_name(
			GTK_WIDGET(gtk_tree_selection_get_tree_view(selection)));
		if (NULL == cdata.name)
			cdata.name = "<UNKNOWN>";
	} else
		cdata.name = NULL;


	gtk_tree_selection_selected_foreach(selection,
		tree_selection_collect_data_helper, &cdata);


	g_slist_foreach(cdata.to_unselect,
		tree_selection_unselect_helper, selection);


    gm_slist_free_null(&cdata.to_unselect);

    return cdata.results;
}
