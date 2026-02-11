savestate_check (void)
{
	if (vpos == 0 && !savestate_state) {
		if (hsync_counter == 0 && input_play == INPREC_PLAY_NORMAL)
			savestate_memorysave ();
		savestate_capture (0);
	}
	if (savestate_state == STATE_DORESTORE) {
		savestate_state = STATE_RESTORE;
		return true;
	} else if (savestate_state == STATE_DOREWIND) {
		savestate_state = STATE_REWIND;
		return true;
	}
	return false;
}
