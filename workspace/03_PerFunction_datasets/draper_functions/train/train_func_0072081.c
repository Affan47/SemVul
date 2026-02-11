nemo_icon_container_search_dialog_hide (GtkWidget *search_dialog,
					    NemoIconContainer *container)
{
	if (container->details->search_entry_changed_id) {
		g_signal_handler_disconnect (container->details->search_entry,
					     container->details->search_entry_changed_id);
		container->details->search_entry_changed_id = 0;
	}

	remove_search_entry_timeout (container);


	send_focus_change (GTK_WIDGET (container->details->search_entry), FALSE);
	gtk_widget_hide (search_dialog);
	gtk_entry_set_text (GTK_ENTRY (container->details->search_entry), "");
}
