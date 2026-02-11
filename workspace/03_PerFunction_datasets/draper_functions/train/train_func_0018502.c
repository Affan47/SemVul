AutoCompleteCompleted() {
	int item = ac.lb->GetSelection();
	char selected[1000];
	selected[0] = '\0';
	if (item != -1) {
		ac.lb->GetValue(item, selected, sizeof(selected));
	} else {
		AutoCompleteCancel();
		return;
	}

	ac.Show(false);

	SCNotification scn = {0};
	scn.nmhdr.code = listType > 0 ? SCN_USERLISTSELECTION : SCN_AUTOCSELECTION;
	scn.message = 0;
	scn.wParam = listType;
	scn.listType = listType;
	Position firstPos = ac.posStart - ac.startLen;
	scn.position = firstPos;
	scn.lParam = firstPos;
	scn.text = selected;
	NotifyParent(scn);

	if (!ac.Active())
		return;
	ac.Cancel();

	if (listType > 0)
		return;

	Position endPos = sel.MainCaret();
	if (ac.dropRestOfWord)
		endPos = pdoc->ExtendWordSelect(endPos, 1, true);
	if (endPos < firstPos)
		return;
	UndoGroup ug(pdoc);
	if (endPos != firstPos) {
		pdoc->DeleteChars(firstPos, endPos - firstPos);
	}
	SetEmptySelection(ac.posStart);
	if (item != -1) {
		pdoc->InsertCString(firstPos, selected);
		SetEmptySelection(firstPos + static_cast<int>(strlen(selected)));
	}
	SetLastXChosen();
}
