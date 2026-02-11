setup_file_list() {
	GtkWidget *file_list = glade_xml_get_widget( app_xml, "file_list" );


	GtkTreeModel *oldmod = gtk_tree_view_get_model(
						GTK_TREE_VIEW(file_list));
  	GtkTreeStore *model;
	if (oldmod)
		model = GTK_TREE_STORE(oldmod);
	else
		{
		model = gtk_tree_store_new(
			NUM_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
		gtk_tree_view_set_model(GTK_TREE_VIEW(file_list),
							GTK_TREE_MODEL(model));
		g_object_unref(model);
		gint col_offset;
  		GtkCellRenderer *renderer = gtk_cell_renderer_text_new ();
 	 	GtkTreeViewColumn *column;


		g_object_set (renderer, "xalign", 0.0, NULL);
		col_offset = gtk_tree_view_insert_column_with_attributes(
					GTK_TREE_VIEW(file_list),
					-1, "Folders",
					renderer, "text",
					FOLDER_COLUMN, NULL);
		column = gtk_tree_view_get_column(GTK_TREE_VIEW(file_list),
							col_offset - 1);
		gtk_tree_view_column_set_clickable(
					GTK_TREE_VIEW_COLUMN(column), TRUE);

		col_offset = gtk_tree_view_insert_column_with_attributes(
					GTK_TREE_VIEW(file_list),
					-1, "Files",
					renderer, "text",
					FILE_COLUMN, NULL);
		column = gtk_tree_view_get_column(GTK_TREE_VIEW(file_list),
							col_offset - 1);
		gtk_tree_view_column_set_clickable(
					GTK_TREE_VIEW_COLUMN(column), TRUE);
		}
	gtk_tree_store_clear(model);
	add_to_tree(model, "Shape Files", "*.vga,*.shp,combos.flx", ShapeArchive);
	add_to_tree(model, "Map Files", "u7chunks", ChunkArchive);
	add_to_tree(model, "Palette Files", "*.pal,palettes.flx", PaletteFile);

#if 0
	add_to_tree(model, "FLEX Files", "*.flx", FlexArchive);
#endif

	gtk_tree_view_expand_all(GTK_TREE_VIEW(file_list));
	gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(file_list), TRUE);
	gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(file_list)), GTK_SELECTION_SINGLE);
}
