set_rfb_cursor(int which) {

	if (! show_cursor) {
		return;
	}
	if (! screen) {
		return;
	}

	if (!cursors[which] || !cursors[which]->rfb) {
		rfbLog("non-existent cursor: which=%d\n", which);
		return;
	} else {
		rfbSetCursor(screen, cursors[which]->rfb);
	}
}
