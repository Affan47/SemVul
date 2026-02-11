foldersel_cb(GtkWidget *widget, gpointer data)
{
	GtkWidget *entry = (GtkWidget *) data;
	FolderItem *item;
	gchar *item_id;
	gint newpos = 0;

	item = foldersel_folder_sel(NULL, FOLDER_SEL_MOVE, NULL, FALSE);
	if (item && (item_id = folder_item_get_identifier(item)) != NULL) {
		gtk_editable_delete_text(GTK_EDITABLE(entry), 0, -1);
		gtk_editable_insert_text(GTK_EDITABLE(entry), item_id, strlen(item_id), &newpos);
		g_free(item_id);
	}
}
