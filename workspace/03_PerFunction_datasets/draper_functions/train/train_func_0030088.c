NotifySavePoint(bool isSavePoint) {
  SCNotification scn; memset(&scn, 0x00, sizeof(scn));
	if (isSavePoint) {
		scn.nmhdr.code = SCN_SAVEPOINTREACHED;
	} else {
		scn.nmhdr.code = SCN_SAVEPOINTLEFT;
	}
	NotifyParent(scn);
}
