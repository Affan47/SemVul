DragDataReceived(GtkWidget *widget, GdkDragContext * ,
                                    gint, gint, GtkSelectionData *selection_data, guint , guint) {
	ScintillaGTK *sciThis = ScintillaFromWidget(widget);
	try {
		sciThis->ReceivedDrop(selection_data);
		sciThis->SetDragPosition(SelectionPosition(invalidPosition));
	} catch (...) {
		sciThis->errorStatus = SC_STATUS_FAILURE;
	}
}
