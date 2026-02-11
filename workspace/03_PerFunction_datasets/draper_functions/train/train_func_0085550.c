brasero_video_disc_clipboard_targets_cb (GtkClipboard *clipboard,
					 GdkAtom *atoms,
					 gint n_atoms,
					 BraseroVideoDisc *self)
{
	if (brasero_clipboard_selection_may_have_uri (atoms, n_atoms))
		gtk_clipboard_request_text (clipboard,
					    (GtkClipboardTextReceivedFunc) brasero_video_disc_clipboard_text_cb,
					    self);
}
