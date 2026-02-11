callbacks_open_layer_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GSList *filenames=NULL;
	GSList *filename=NULL;

	screen.win.gerber =
	gtk_file_chooser_dialog_new ("Open Gerber, drill, or pick & place file(s)...",
				     NULL,
				     GTK_FILE_CHOOSER_ACTION_OPEN,
				     GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				     GTK_STOCK_OPEN,   GTK_RESPONSE_ACCEPT,
				     NULL);

	gtk_file_chooser_set_select_multiple((GtkFileChooser *) screen.win.gerber, TRUE);
	gtk_file_chooser_set_current_folder ((GtkFileChooser *) screen.win.gerber,
		mainProject->path);
	gtk_widget_show (screen.win.gerber);
	if (gtk_dialog_run ((GtkDialog*)screen.win.gerber) == GTK_RESPONSE_ACCEPT) {
		filenames =
		    gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER (screen.win.gerber));

		g_free (mainProject->path);
		mainProject->path = gtk_file_chooser_get_current_folder ((GtkFileChooser *) screen.win.gerber);
	}
	gtk_widget_destroy (screen.win.gerber);


	for (filename=filenames; filename; filename=filename->next) {
		gerbv_open_layer_from_filename (mainProject, filename->data);
	}
	g_slist_free(filenames);

	gerbv_render_zoom_to_fit_display (mainProject, &screenRenderInfo);
	render_refresh_rendered_image_on_screen();
	callbacks_update_layer_tree();

	return;
}
