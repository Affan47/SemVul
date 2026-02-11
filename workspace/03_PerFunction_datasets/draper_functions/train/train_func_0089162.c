cb_Edit_Undo (wxCommandEvent &event)
{
	if (undoStack.empty ())
		return;
	delete graph;
	graph = undoStack.pop ().getGraph ();
	canvas->redraw ();
	if (undoStack.empty ()) {
		edit_Undo->Enable (false);
		setUndoText (wxT(""));
	} else
		setUndoText (undoStack.top ().getMessage ());
}
