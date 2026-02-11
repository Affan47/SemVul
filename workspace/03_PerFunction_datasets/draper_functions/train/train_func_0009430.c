StoreOnClipboard(SelectionText *clipText) {
	GtkClipboard *clipBoard =
		gtk_widget_get_clipboard(GTK_WIDGET(PWidget(wMain)), atomClipboard);
	if (clipBoard == NULL)
		return;

	if (gtk_clipboard_set_with_data(clipBoard, clipboardCopyTargets, nClipboardCopyTargets,
				    ClipboardGetSelection, ClipboardClearSelection, clipText)) {
		gtk_clipboard_set_can_store(clipBoard, clipboardCopyTargets, nClipboardCopyTargets);
	}
}
