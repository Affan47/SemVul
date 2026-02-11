AutoCompleteCharacterDeleted() {
	if (sel.MainCaret() < ac.posStart - ac.startLen) {
		AutoCompleteCancel();
	} else if (ac.cancelAtStartPos && (sel.MainCaret() <= ac.posStart)) {
		AutoCompleteCancel();
	} else {
		AutoCompleteMoveToCurrentWord();
	}
  SCNotification scn; memset(&scn, 0x00, sizeof(scn));
	scn.nmhdr.code = SCN_AUTOCCHARDELETED;
	scn.wParam = 0;
	scn.listType = 0;
	NotifyParent(scn);
}
