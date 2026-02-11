defpref_pathselect(GtkWidget *widget, gpointer user_data)
{
struct defpref_data *data;
gint type = GPOINTER_TO_INT(user_data);
gchar **path;
GtkWidget *entry;
gboolean r;

	DB( g_print("\n[ui-pref] path select\n") );

	data = g_object_get_data(G_OBJECT(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW)), "inst_data");

	switch( type )
	{
		case 1:
			path = &PREFS->path_hbfile;
			entry = data->ST_path_hbfile;
			break;
		case 2:
			path = &PREFS->path_import;
			entry = data->ST_path_import;
			break;
		case 3:
			path = &PREFS->path_export;
			entry = data->ST_path_export;
			break;
		default:
			return;
	}

	DB( g_print(" - hbfile %p %s at %p\n" , PREFS->path_hbfile, PREFS->path_hbfile, &PREFS->path_hbfile) );
	DB( g_print(" - import %p %s at %p\n" , PREFS->path_import, PREFS->path_import, &PREFS->path_import) );
	DB( g_print(" - export %p %s at %p\n" , PREFS->path_export, PREFS->path_export, &PREFS->path_export) );


	DB( g_print(" - before: %s %p\n" , *path, path) );

	r = ui_file_chooser_folder(GTK_WINDOW(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW)), "title", path);


	DB( g_print(" - after: %s\n", *path) );

	if( r == TRUE )
		gtk_entry_set_text(GTK_ENTRY(entry), *path);


}
