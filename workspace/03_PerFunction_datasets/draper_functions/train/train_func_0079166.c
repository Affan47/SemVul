catalog_ready_cb (GObject  *catalog,
		  GError   *error,
		  gpointer  user_data)
{
	CopyOpData *cod = user_data;
	int         position;
	GList      *scan;
	char       *buffer;
	gsize       size;
	GFile      *gio_file;

	if (error != NULL) {
		cod->ready_callback (G_OBJECT (cod->file_source), error, cod->user_data);
		copy_op_data_free (cod);
		return;
	}

	cod->catalog = (GthCatalog *) catalog;

	if (cod->destination_position >= 0)
		gth_catalog_set_order (cod->catalog, "general::unsorted", FALSE);

	position = cod->destination_position;
	for (scan = cod->files; scan; scan = scan->next) {
		gth_catalog_insert_file (cod->catalog, (GFile *) scan->data, position);
		if (cod->destination_position >= 0)
			position += 1;
	}

	buffer = gth_catalog_to_data (cod->catalog, &size);
	gio_file = gth_catalog_file_to_gio_file (cod->destination->file);
	_g_file_write_async (gio_file,
			     buffer,
			     size,
			     TRUE,
			     G_PRIORITY_DEFAULT,
			     NULL,
			     copy__catalog_save_done_cb,
			     cod);

	g_object_unref (gio_file);
}
