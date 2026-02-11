BookmarkNext() {
	int lineno = GetCurrentLineNumber();
	int nextLine = SendEditor(SCI_MARKERNEXT, lineno + 1, 1 << ANE_MARKER_BOOKMARK);
	if (nextLine < 0 || nextLine == lineno) {
		if(props->GetInt("editor.wrapbookmarks")) {
			int nextLine1 = SendEditor(SCI_MARKERNEXT, 0, 1 << ANE_MARKER_BOOKMARK);
			if (nextLine1 < 0 || nextLine1 == lineno) {
				gdk_beep();
			} else {
				SendEditor(SCI_ENSUREVISIBLE, nextLine1);
				SendEditor(SCI_GOTOLINE, nextLine1);
			}
		}
	} else {
		SendEditor(SCI_ENSUREVISIBLE, nextLine);
		SendEditor(SCI_GOTOLINE, nextLine);
	}
}
