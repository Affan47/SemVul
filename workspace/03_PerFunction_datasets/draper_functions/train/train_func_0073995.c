SelectionGet(GtkWidget *widget,
                                GtkSelectionData *selection_data, guint info, guint) {
	ScintillaGTK *sciThis = ScintillaFromWidget(widget);
	try {

		if (SelectionOfGSD(selection_data) == GDK_SELECTION_PRIMARY) {
			if (sciThis->primary.s == NULL) {
				sciThis->CopySelectionRange(&sciThis->primary);
			}
			sciThis->GetSelection(selection_data, info, &sciThis->primary);
		}
	} catch (...) {
		sciThis->errorStatus = SC_STATUS_FAILURE;
	}
}
