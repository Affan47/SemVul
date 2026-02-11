disable_cursor_shape_updates(rfbScreenInfoPtr s) {
	rfbClientIteratorPtr iter;
	rfbClientPtr cl;
	static int changed = 0;
	int count = 0;

	if (! s || ! s->clientHead) {
		return;
	}
	if (unixpw_in_progress) return;

	iter = rfbGetClientIterator(s);
	while( (cl = rfbClientIteratorNext(iter)) ) {
		ClientData *cd;
		cd = (ClientData *) cl->clientData;

		if (cl->enableCursorShapeUpdates) {
			if (cd) {
				cd->had_cursor_shape_updates = 1;
			}
			count++;
			if (debug_pointer) {
				rfbLog("%s disable HCSU\n", cl->host);
			}
		}
		if (cl->enableCursorPosUpdates) {
			if (cd) {
				cd->had_cursor_pos_updates = 1;
			}
			count++;
			if (debug_pointer) {
				rfbLog("%s disable HCPU\n", cl->host);
			}
		}

		cl->enableCursorShapeUpdates = FALSE;
		cl->enableCursorPosUpdates = FALSE;
		cl->cursorWasChanged = FALSE;
	}
	rfbReleaseClientIterator(iter);

	if (count) {
		changed = 1;
	}
}
