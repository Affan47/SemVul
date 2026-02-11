cursor_end()
{
	cursorline_get();
	int c = tag_count_selectable_tags_in_group(cursor_line, cursor.tag_group);
	cursor.tag_idx = c-1;
	if (edit()) {
		char *e = tag_get_selectable_tag(cursor_line, cursor.tag_idx, cursor.tag_group);
		if (e) cursor_tag_micropos = tag_get_microsize(e) - 1;
	}
	update_visual_info();
	update_misc_info();
	return 1;
}
