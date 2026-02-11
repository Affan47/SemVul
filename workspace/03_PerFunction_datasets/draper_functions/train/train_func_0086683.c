fi_gui_init(void)
{
	fi_sources = htable_create(HASH_KEY_SELF, 0);

	{
		GtkTreeViewColumn *column;
		GtkTreeView *tv;

		tv = GTK_TREE_VIEW(gui_main_window_lookup("treeview_download_aliases"));
		treeview_download_aliases = tv;

		store_aliases = gtk_list_store_new(1, G_TYPE_STRING);
		gtk_tree_view_set_model(tv, GTK_TREE_MODEL(store_aliases));

		column = gtk_tree_view_column_new_with_attributes(_("Aliases"),
					create_text_cell_renderer(0.0),
					"text", 0,
					(void *) 0);
		configure_column(column);
		gtk_tree_view_column_set_sort_column_id(column, 0);
    	gtk_tree_view_append_column(tv, column);

		tree_view_set_fixed_height_mode(tv, TRUE);
		drag_attach_text(GTK_WIDGET(tv), fi_gui_get_alias);
	}

	{
		static const struct {
			enum c_src id;
			const char *title;
		} tab[] = {
   			{ c_src_host, 	 	N_("Host"), },
   			{ c_src_country, 	N_("Country"), },
   			{ c_src_server,  	N_("Server"), },
   			{ c_src_range, 	 	N_("Range"), },
   			{ c_src_progress,	N_("Progress"), },
   			{ c_src_status,	 	N_("Status"), },
		};
		GtkTreeView *tv;
		unsigned i;

		STATIC_ASSERT(c_src_num == G_N_ELEMENTS(tab));

		tv = GTK_TREE_VIEW(gui_main_window_lookup("treeview_download_sources"));
		treeview_download_sources = tv;

		store_sources = gtk_list_store_new(1, G_TYPE_POINTER);
		gtk_tree_view_set_model(tv, GTK_TREE_MODEL(store_sources));

		for (i = 0; i < G_N_ELEMENTS(tab); i++) {
			GtkCellRenderer *renderer;

			renderer = tab[i].id == c_src_progress
						? gtk_cell_renderer_progress_new()
						: NULL;
    		add_column(tv, tab[i].id, _(tab[i].title), 0.0,
				renderer, render_sources);
		}

		gtk_tree_view_set_headers_clickable(tv, FALSE);
		gtk_tree_selection_set_mode(gtk_tree_view_get_selection(tv),
			GTK_SELECTION_MULTIPLE);
		tree_view_restore_widths(tv, PROP_SOURCES_COL_WIDTHS);
		tree_view_set_fixed_height_mode(tv, TRUE);

		widget_add_popup_menu(GTK_WIDGET(tv), fi_gui_sources_get_popup_menu);
	}

	fi_gui_details_treeview_init();
	fi_gui_common_init();
}
