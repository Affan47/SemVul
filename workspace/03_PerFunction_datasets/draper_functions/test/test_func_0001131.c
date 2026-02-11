ui_mainwindow_save(GtkWidget *widget, gpointer user_data)
{
struct hbfile_data *data;
gboolean saveas = GPOINTER_TO_INT(user_data);
gchar *filename = NULL;
gint r = XML_UNSET;

	DB( g_print("\n[ui-mainwindow] save\n") );

	data = g_object_get_data(G_OBJECT(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW)), "inst_data");

	if( GLOBALS->hbfile_is_new == TRUE )
		saveas = 1;

	if(saveas == 1)
	{
		if(ui_file_chooser_xhb(GTK_FILE_CHOOSER_ACTION_SAVE, &filename) == TRUE)
		{
			DB( g_print(" + should save as %s\n", GLOBALS->xhb_filepath) );
			hbfile_change_filepath(filename);
			homebank_backup_current_file(GLOBALS->xhb_filepath);
			homebank_file_ensure_xhb();
			r = homebank_save_xml(GLOBALS->xhb_filepath);
			GLOBALS->hbfile_is_new = FALSE;

		}
		else
			return;
	}
	else
	{
		DB( g_print(" + should quick save %s\n", GLOBALS->xhb_filepath) );
		homebank_backup_current_file(GLOBALS->xhb_filepath);
		homebank_file_ensure_xhb();
		r = homebank_save_xml(GLOBALS->xhb_filepath);
	}


	if(r == XML_OK)
	{
		GLOBALS->changes_count = 0;
		ui_mainwindow_update(GLOBALS->mainwindow, GINT_TO_POINTER(UF_TITLE+UF_SENSITIVE+UF_VISUAL));
	}
	else
	{
	gchar *msg = _("I/O error for file %s.");

		ui_dialog_msg_infoerror(GTK_WINDOW(data->window), GTK_MESSAGE_ERROR,
			_("File error"),
			msg,
			GLOBALS->xhb_filepath
			);

	}


}
