on_main_window_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{

	if (file_modified && ask_to_save(widget, current_filename))
	{
		save_keyboard_file (widget, &current_filename, &key_list);
	}
	KTKeyList_clear (&key_list);
	gtk_main_quit();
	gtk_exit (0);
	return FALSE;
}
