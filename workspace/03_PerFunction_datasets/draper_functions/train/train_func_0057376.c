addmap(int i, int explicit)
{
	if (i < 0 || i >= MAX_NR_KEYMAPS)
		lkfatal(_("addmap called with bad index %d"), i);

	if (!defining[i]) {
		if (keymaps_line_seen && !explicit)
			lkfatal(_("adding map %d violates explicit keymaps line"), i);

		defining[i] = 1;
		if (max_keymap <= i)
			max_keymap = i + 1;
	}
}
