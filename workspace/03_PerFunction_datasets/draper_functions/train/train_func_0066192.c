MarginClick(int position, int modifiers) {
	int lineClick = SendEditor(SCI_LINEFROMPOSITION, position);

	if (modifiers & SCMOD_SHIFT) {
		FoldCloseAll();
	} else if (modifiers & SCMOD_CTRL) {
		FoldOpenAll();
	} else if (SendEditor(SCI_GETFOLDLEVEL, lineClick) & SC_FOLDLEVELHEADERFLAG) {
		if (modifiers & SCMOD_SHIFT) {

			SendEditor(SCI_SETFOLDEXPANDED, lineClick, 1);
			Expand(lineClick, true, true, 100);
		} else if (modifiers & SCMOD_CTRL) {
			if (SendEditor(SCI_GETFOLDEXPANDED, lineClick)) {

				SendEditor(SCI_SETFOLDEXPANDED, lineClick, 0);
				Expand(lineClick, false, true, 0);
			} else {

				SendEditor(SCI_SETFOLDEXPANDED, lineClick, 1);
				Expand(lineClick, true, true, 100);
			}
		} else {

			SendEditor(SCI_TOGGLEFOLD, lineClick);
		}
	}
	return true;
}
