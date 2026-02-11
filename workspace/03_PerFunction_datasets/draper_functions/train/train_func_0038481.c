AutoCompleteCancel() {
	if (ac.Active()) {
		SCNotification scn; memset(&scn, 0x00, sizeof(scn));
		scn.nmhdr.code = SCN_AUTOCCANCELLED;
		scn.wParam = 0;
		scn.listType = 0;
		NotifyParent(scn);
	}
	ac.Cancel();
}
