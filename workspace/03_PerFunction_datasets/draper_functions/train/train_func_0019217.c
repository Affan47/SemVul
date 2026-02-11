SetFocusState(bool focusState) {
	hasFocus = focusState;
	NotifyFocus(hasFocus);
	if (hasFocus) {
		ShowCaretAtCurrentPosition();
	} else {
		CancelModes();
		DropCaret();
	}
}
