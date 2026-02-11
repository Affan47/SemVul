help_open(struct view *view, enum open_flags flags)
{
	enum keymap keymap;

	reset_view(view);
	view->p_restore = TRUE;
	add_line_text(view, "Quick reference for tig keybindings:", LINE_DEFAULT);
	add_line_text(view, "", LINE_DEFAULT);

	for (keymap = 0; keymap < ARRAY_SIZE(keymap_map); keymap++)
		help_open_keymap(view, keymap);

	return TRUE;
}
