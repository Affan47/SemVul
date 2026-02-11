select_mode_post(bool lastpos)
{
	if (cursor_select) {
		if (cursor_select_start != -1ULL) {
			if (cursor_tag_class == tag_class_edit) {
				if (lastpos && cursor_select_cursor_length != uint32(-1)) {
					FileOfs s, e;
					pselect_get(&s, &e);
					if (e != cursor_tag_offset+cursor_select_cursor_length) {
						pselect_add(cursor_select_start, cursor_tag_offset+cursor_select_cursor_length);
					}
				} else {
					pselect_add(cursor_select_start, cursor_tag_offset);
				}
			} else if (cursor_tag_class == tag_class_sel && cursor_select_cursor_length != uint32(-1)) {
				pselect_add(cursor_select_start, cursor_select_start+cursor_select_cursor_length);
			}
		}
	}
}
