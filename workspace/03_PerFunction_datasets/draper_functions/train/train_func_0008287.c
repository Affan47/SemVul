search_gui_color_for_record(const record_t * const rc)
{
	const results_set_t *rs = rc->results_set;

	if (SR_SPAM & rc->flags) {
		return GUI_COLOR_SPAM;
	} else if (ST_HOSTILE & rs->status) {
		return GUI_COLOR_HOSTILE;
	} else if ((ST_SPAM & rs->status) && !(ST_BROWSE & rs->status)) {
		return GUI_COLOR_MAYBE_SPAM;
	} else if (rs->status & ST_UNREQUESTED) {
		return GUI_COLOR_UNREQUESTED;
	} else if (rs->status & ST_BANNED_GUID) {
		return GUI_COLOR_BANNED_GUID;
	} else if (rc->flags & SR_MEDIA) {
		return GUI_COLOR_MEDIA;
	} else if (rc->flags & (SR_IGNORED | SR_OWNED | SR_SHARED)) {
		return GUI_COLOR_IGNORED;
	} else if (rc->flags & (SR_DOWNLOADED | SR_PARTIAL)) {
		return GUI_COLOR_DOWNLOADING;
	} else if (ST_ALIEN & rs->status) {
		return GUI_COLOR_ALIEN;
	} else if (rc->flags & SR_PARTIAL_HIT) {
		return rc->flags & SR_PUSH ?
			GUI_COLOR_PARTIAL_PUSH : GUI_COLOR_PARTIAL;
	} else if (rc->flags & SR_PUSH) {
		return ST_PUSH_PROXY & rs->status ?
			GUI_COLOR_PUSH_PROXY : GUI_COLOR_PUSH;
	} else {
		return GUI_COLOR_DEFAULT;
	}
}
