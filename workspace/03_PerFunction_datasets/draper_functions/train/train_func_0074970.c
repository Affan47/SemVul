cursor_right()
{
	cursorline_get();
	if (cursor.tag_idx < tag_count_selectable_tags_in_group(cursor_line, cursor.tag_group)-1) {
		cursor.tag_idx++;
		update_visual_info();
		update_misc_info();
		return 1;
	} else {
		if (cursor_down(1)) {
			cursor_home();
			return 1;
		}
	}
	return 0;
}
