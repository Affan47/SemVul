SelectGPSButtonPress( GtkWidget *Widget, gpointer Data )
{

	GtkWidget *GPSDataDialog;
	GtkWidget *ErrorDialog;
	char* FileName;
	char* Scratch;

	if (GPXOpenDir == NULL)
	{

		GPXOpenDir = g_key_file_get_value(GUISettings, "default", "gpxopendir", NULL);
	}


	GPSDataDialog = gtk_file_chooser_dialog_new ("Select GPS Data...",
			GTK_WINDOW(MatchWindow),
			GTK_FILE_CHOOSER_ACTION_OPEN,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
			NULL);

	gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(GPSDataDialog), FALSE);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(GPSDataDialog), GPXOpenDir);


	if (gtk_dialog_run (GTK_DIALOG (GPSDataDialog)) == GTK_RESPONSE_ACCEPT)
	{

		FileName = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(GPSDataDialog));


		if (GPSData)
		{

			FreePointList(GPSData);
		}


		Scratch = malloc(sizeof(char) * (strlen(FileName) + 100));


		gtk_widget_hide(GPSDataDialog);


		ErrorDialog = gtk_message_dialog_new (GTK_WINDOW(MatchWindow),
			GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			0,
			"Loading GPS data from file... Won't be a moment...");
		gtk_widget_show(ErrorDialog);
		GtkGUIUpdate();


		GPSData = ReadGPX(FileName);


		gtk_widget_destroy(ErrorDialog);


		if (GPSData)
		{


			snprintf(Scratch, strlen(FileName)+100,
					"Read from: %s", strrchr(FileName, G_DIR_SEPARATOR)+1);
			gtk_label_set_text(GTK_LABEL(GPSSelectedLabel), Scratch);
		} else {


			snprintf(Scratch, strlen(FileName)+100,
					"Reading from: No file");
			gtk_label_set_text(GTK_LABEL(GPSSelectedLabel), Scratch);

			ErrorDialog = gtk_message_dialog_new (GTK_WINDOW(MatchWindow),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_ERROR,
					GTK_BUTTONS_CLOSE,
					"Unable to read file %s for some reason. Please try again",
					FileName);
			gtk_dialog_run (GTK_DIALOG (ErrorDialog));
			gtk_widget_destroy (ErrorDialog);
		}


		free(Scratch);
		g_free(FileName);
	}


	if (GPXOpenDir)
	{
		g_free(GPXOpenDir);
	}
	GPXOpenDir = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(GPSDataDialog));


	gtk_widget_destroy (GPSDataDialog);

}
