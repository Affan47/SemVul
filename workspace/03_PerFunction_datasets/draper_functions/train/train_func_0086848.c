on_open1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)


{
	GtkWidget *open_dialog;
	KTKeyList new_key_list;
	char *filename,
	     *manufacturer,
	     *model;
	int vendor_id, product_id;


	if (file_modified && ask_to_save(GTK_WIDGET(menuitem), current_filename))
	{
		save_keyboard_file (GTK_WIDGET(menuitem), &current_filename, &key_list);
	}
	open_dialog = gtk_file_chooser_dialog_new (_("Open keyboard file"),
					GTK_WINDOW ( gtk_widget_get_toplevel (GTK_WIDGET(menuitem)) ),
					GTK_FILE_CHOOSER_ACTION_OPEN,
					GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					NULL);
	if (gtk_dialog_run (GTK_DIALOG (open_dialog)) == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (open_dialog));

		if (read_keyboard_file (&new_key_list, &manufacturer, &model,
		                        &vendor_id, &product_id, filename))
		{


			if (evdev_bus_id(current_evdev) != BUS_USB)
			{
				usb_vendor_id = vendor_id;
				usb_product_id = product_id;
			}
			if (current_filename)
			{
				g_free (current_filename);
			}
			current_filename = filename;

			gtk_entry_set_text (
				GTK_ENTRY( lookup_widget(GTK_WIDGET(menuitem), "manufacturer_entry") ),
				manufacturer);
			free (manufacturer);
			gtk_entry_set_text (
				GTK_ENTRY( lookup_widget(GTK_WIDGET(menuitem), "model_entry") ),
				model);
			free (model);

			KTKeyList_clear (&key_list);
			key_list = new_key_list;
			reload_key_treeview (&key_list, GTK_WIDGET(menuitem));
			file_modified = FALSE;
			selected_key = NULL;
			clear_key_settings_frame (GTK_WIDGET( menuitem ));
		}
		else
		{

			g_free (filename);
		}
	}

	gtk_widget_destroy (open_dialog);
}
