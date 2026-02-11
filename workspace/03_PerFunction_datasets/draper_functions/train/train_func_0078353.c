gnet_stats_gui_horizon_init(void)
{
	static const gchar * const titles[num_c_horizon] = {
		N_("Hops"),
		N_("Nodes"),
		N_("Files"),
		N_("Size")
	};
	GType types[] = {
		G_TYPE_INT,
		G_TYPE_STRING,
		G_TYPE_STRING,
		G_TYPE_STRING
	};
	GtkTreeView *treeview;
	GtkTreeModel *model;
	guint32 width[num_c_horizon];
	c_horizon_t n;

	STATIC_ASSERT(num_c_horizon == G_N_ELEMENTS(types));
	model = GTK_TREE_MODEL(gtk_list_store_newv(G_N_ELEMENTS(types), types));
	treeview = treeview_gnet_stats_horizon = GTK_TREE_VIEW(
	    gui_main_window_lookup("treeview_gnet_stats_horizon"));

	gui_prop_get_guint32(PROP_GNET_STATS_HORIZON_COL_WIDTHS,
		width, 0, G_N_ELEMENTS(width));
	for (n = 0; n < G_N_ELEMENTS(width); n++) {
		GtkTreeIter iter;
		gint i;

		for (i = 0; n == c_horizon_hops && i < HSEP_N_MAX; i++) {
			gtk_list_store_append(GTK_LIST_STORE(model), &iter);
			gtk_list_store_set(GTK_LIST_STORE(model), &iter,
				c_horizon_hops, i + 1,
				c_horizon_nodes, "-",
				c_horizon_files, "-",
				c_horizon_size, "-",
				(-1));
		}
		add_column(treeview, n, width[n], (gfloat) (n != 0), _(titles[n]));
	}
	gtk_tree_view_set_model(treeview, model);
	g_object_unref(model);
	tree_view_set_fixed_height_mode(treeview, TRUE);
}
