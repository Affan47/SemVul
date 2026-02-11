gw_cm_load_disk_node ( GtkCTree *ctree, GtkCTreeNode *parent, GWDBDisk *disk) {
	gchar *text[1];
	GtkCTreeNode *node = NULL;
	GdkPixmap *pix = NULL;
	GdkBitmap *msk = NULL;
	GWDBFile **files = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
	int i = 0;


	g_strdup_to_gtk_text ( gw_db_disk_get_name ( disk), text[0]);
	pix = gw_helper_db_disk_get_pixmap ( disk);
	msk = gw_helper_db_disk_get_bitmap ( disk);
	node = gtk_ctree_insert_node ( ctree, parent, NULL, text, 5, pix, msk, pix, msk, FALSE, FALSE);
	g_free ( text[0]);
	gtk_ctree_node_set_row_data ( ctree, node, gw_db_disk_get_ref ( disk));


	if ( (files = plugin->gw_db_disk_get_db_files ( context, gw_db_disk_get_ref ( disk))) != NULL) {
		for ( i = 0; files[i] != NULL; i++) {
			if ( gw_db_file_is_real_directory ( files[i])) {
				gw_cm_load_file_node ( ctree, node, files[i]);
			} else {}

			gw_db_file_free ( files[i]);
		}

		g_free ( files);
	} else {}

	return 0;
}
