hb_export_qif_account_all(gchar *filename)
{
GIOChannel *io;
gchar *newname;
GList *list;

	newname = homebank_filepath_with_extention(filename, "qif");

	io = g_io_channel_new_file(newname, "w", NULL);
	if(io == NULL)
	{
		g_message("file error on: %s", newname);

	}
	else
	{


		list = g_hash_table_get_values(GLOBALS->h_acc);
		while (list != NULL)
		{
		Account *item = list->data;

			hb_export_qif_elt_acc(io, item);
			hb_export_qif_elt_txn(io, item);

			list = g_list_next(list);
		}
		g_list_free(list);

		g_io_channel_unref (io);
	}

	g_free(newname);

}
