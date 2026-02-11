OkSelectContactDialog(GtkWidget * widget, SelectContactData * data)
{
	GList *sel;
	PhonebookEntry *pbEntry;
	gchar *key;

	if ((sel = GTK_CLIST(data->clist)->selection) != NULL) {
		D_SpeedDial *d = (D_SpeedDial *) g_malloc(sizeof(D_SpeedDial));

		gtk_clist_freeze(GTK_CLIST(clist));

		pbEntry = gtk_clist_get_row_data(GTK_CLIST(data->clist),
						 GPOINTER_TO_INT(sel->data));

		gtk_clist_get_text(GTK_CLIST(clist), selectedKey, 0, &key);

		gtk_clist_set_text(GTK_CLIST(clist), selectedKey, 1, pbEntry->entry.name);
		gtk_clist_set_text(GTK_CLIST(clist), selectedKey, 2, pbEntry->entry.number);

		d->entry.number = *key - '0';
		d->entry.memory_type = pbEntry->entry.memory_type + 2;
		d->entry.location = pbEntry->entry.location;

		gtk_clist_set_row_data_full(GTK_CLIST(clist), selectedKey,
					    (gpointer) d, DestroyCListData);

		gtk_clist_sort(GTK_CLIST(clist));
		gtk_clist_thaw(GTK_CLIST(clist));
	}

	gtk_widget_destroy(GTK_WIDGET(data->clist));
	gtk_widget_destroy(GTK_WIDGET(data->clistScrolledWindow));
	gtk_widget_destroy(GTK_WIDGET(data->dialog));
}
