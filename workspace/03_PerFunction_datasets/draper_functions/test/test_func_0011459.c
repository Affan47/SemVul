real_active (NemoWindowSlot *slot)
{
	NemoWindow *window;
	NemoWindowPane *pane;
	int page_num;

	window = nemo_window_slot_get_window (slot);
	pane = slot->pane;
	page_num = gtk_notebook_page_num (GTK_NOTEBOOK (pane->notebook),
					  GTK_WIDGET (slot));
	g_assert (page_num >= 0);

	gtk_notebook_set_current_page (GTK_NOTEBOOK (pane->notebook), page_num);


	nemo_window_sync_status (window);
	nemo_window_sync_allow_stop (window, slot);
	nemo_window_sync_title (window, slot);
	nemo_window_sync_zoom_widgets (window);
	nemo_window_pane_sync_location_widgets (slot->pane);
	nemo_window_pane_sync_search_widgets (slot->pane);

	if (slot->viewed_file != NULL) {
		nemo_window_load_view_as_menus (window);
		nemo_window_load_extension_menus (window);
	}
}
