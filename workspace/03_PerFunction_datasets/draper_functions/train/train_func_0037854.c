ReceivedSelection(GtkSelectionData *selection_data) {
	try {
		if ((SelectionOfGSD(selection_data) == atomClipboard) ||
		        (SelectionOfGSD(selection_data) == GDK_SELECTION_PRIMARY)) {
			if ((atomSought == atomUTF8) && (LengthOfGSD(selection_data) <= 0)) {
				atomSought = atomString;
				gtk_selection_convert(GTK_WIDGET(PWidget(wMain)),
				        SelectionOfGSD(selection_data), atomSought, GDK_CURRENT_TIME);
			} else if ((LengthOfGSD(selection_data) > 0) &&
			        ((TypeOfGSD(selection_data) == GDK_TARGET_STRING) || (TypeOfGSD(selection_data) == atomUTF8))) {
				SelectionText selText;
				GetGtkSelectionText(selection_data, selText);

				UndoGroup ug(pdoc);
				if (SelectionOfGSD(selection_data) != GDK_SELECTION_PRIMARY) {
					ClearSelection(multiPasteMode == SC_MULTIPASTE_EACH);
				}
				SelectionPosition selStart = sel.IsRectangular() ?
					sel.Rectangular().Start() :
					sel.Range(sel.Main()).Start();

				if (selText.rectangular) {
					PasteRectangular(selStart, selText.s, selText.len);
				} else {
					InsertPaste(selStart, selText.s, selText.len);
				}
				EnsureCaretVisible();
			}
		}


		Redraw();
	} catch (...) {
		errorStatus = SC_STATUS_FAILURE;
	}
}
