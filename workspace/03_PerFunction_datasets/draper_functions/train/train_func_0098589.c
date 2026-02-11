settings_window_layouts_populate()
{
	START_FUNC
	GtkTreeIter iter;
	GtkCellRenderer *cell;
	DIR *dp=opendir(DATADIR "/layouts");
	struct dirent *ep;
	gchar *name;
	struct layout *layout;
	struct layout_infos *infos;

	if (dp!=NULL) {
		if (settings_window->layout_list) {
			gtk_list_store_clear(settings_window->layout_list);
			g_object_unref(G_OBJECT(settings_window->layout_list));
		}
		settings_window->layout_list=gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
		cell=gtk_cell_renderer_text_new();
		gtk_cell_layout_pack_start(
			GTK_CELL_LAYOUT(gtk_builder_get_object(settings_window->gtkbuilder, "flo_layouts")),
			cell, FALSE);
		gtk_cell_layout_set_attributes(
			GTK_CELL_LAYOUT(gtk_builder_get_object(settings_window->gtkbuilder, "flo_layouts")),
			cell, "text", 0, NULL);
		while ((ep=readdir(dp))) {
			if (ep->d_name[0]!='.') {
				name=g_strdup_printf(DATADIR "/layouts/%s", ep->d_name);
				layout=layoutreader_new(name, NULL, DATADIR "/relaxng/florence.rng");
				layoutreader_element_open(layout, "layout");
				infos=layoutreader_infos_new(layout);
				gtk_list_store_append(settings_window->layout_list, &iter);
				gtk_list_store_set(settings_window->layout_list, &iter, 0, infos->name, 1, name, -1);
				layoutreader_infos_free(infos);
				layoutreader_free(layout);
				g_free(name);
			}
		}
		closedir(dp);
		gtk_combo_box_set_model(GTK_COMBO_BOX(gtk_builder_get_object(
				settings_window->gtkbuilder, "flo_layouts")),
			GTK_TREE_MODEL(settings_window->layout_list));
	} else flo_error(_("Couldn't open directory %s"), DATADIR "/layouts");
	END_FUNC
}
