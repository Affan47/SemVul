gcrp_key_press_event (GtkWidget           *popup_window,
		      GdkEventKey         *event,
		      GncCellRendererPopup *cell)
{
	if (event->keyval != GDK_Escape &&
	    event->keyval != GDK_Return &&
	    event->keyval != GDK_KP_Enter &&
	    event->keyval != GDK_ISO_Enter &&
	    event->keyval != GDK_3270_Enter) {
		return FALSE;
	}
	if (event->keyval == GDK_Escape) {
		cell->editing_canceled = TRUE;
	} else {
		cell->editing_canceled = FALSE;
	}
	gnc_cell_renderer_popup_hide (cell);

	return TRUE;
}
