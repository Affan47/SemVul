search_engine_add_item ( GtkCList *clist, GWDBFile *file, GWDBCategory *category) {
	gint result = -1;
	gchar *info[7];
	gint row, i;
	gchar *text_utf8 = NULL;
	gchar *location = NULL, *tmp = NULL;
	struct search_item_info *search_item = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = NULL;
	GWDBDisk *disk = NULL;


	if ( context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			if ( file != NULL ) {
				disk = plugin->gw_db_file_get_db_disk ( context, gw_db_file_get_ref ( file));
				g_strdup_to_gtk_text ( gw_db_file_get_name ( file), info[0]);
				g_strdup_to_gtk_text ( gw_db_disk_get_name ( disk), info[1]);
				g_strdup_to_gtk_text ( (location = plugin->gw_db_file_get_location ( context, gw_db_file_get_ref ( file))), info[2]);
				text_utf8 = gw_l_byte_to_str_format ( gw_db_file_get_size ( file));
				g_strdup_to_gtk_text ( text_utf8, info[3]);
				g_free ( text_utf8);
				tmp = gw_helper_db_file_get_cdate_to_str ( file);
				g_strdup_to_gtk_text ( tmp, info[4]);
				g_free ( tmp);
				g_strdup_to_gtk_text ( gw_db_category_get_name ( category), info[5]);
				g_strdup_to_gtk_text ( gw_db_file_get_description ( file), info[6]);
				gw_str_replace_char ( info[6], '\n', ' ');

				row = gtk_clist_append ( clist, info);

				search_item = search_item_info_new ( );
				if ( gw_db_file_is_real_directory ( file)) {
					search_item_info_set_type ( search_item, SEARCH_ITEM_TYPE_FOLDER);
				} else {
					search_item_info_set_type ( search_item, SEARCH_ITEM_TYPE_FILE);
				}
				search_item_info_set_name ( search_item, g_strdup ( gw_db_file_get_name ( file)));
				search_item_info_set_disk ( search_item, g_strdup ( gw_db_disk_get_name ( disk)));
				search_item_info_set_path ( search_item, location);
				search_item_info_set_size ( search_item, gw_db_file_get_size ( file));
				search_item_info_set_date ( search_item, gw_db_file_get_cdate ( file));
				search_item_info_set_category ( search_item, category);
				if ( gw_db_file_get_description ( file) != NULL ) {
					search_item_info_set_description ( search_item, g_strdup ( gw_db_file_get_description ( file)));
				}


				gtk_clist_set_row_data_full ( clist, row, (struct search_item_info*)search_item, NULL);

				if ( gw_db_file_is_real_directory ( file)) {
					gtk_clist_set_pixtext ( clist, row, 0, info[0], 5, PixFolder, MskFolder);
				} else {
					gtk_clist_set_pixtext ( clist, row, 0, info[0], 5, PixFile, MskFile);
				}

				for ( i = 0; i <= 6; i++) {
					g_free ( info[i]);
				}
				gw_db_disk_free ( disk);

				result = 0;
			}
		} else {}
	} else {}

	return result;
}
