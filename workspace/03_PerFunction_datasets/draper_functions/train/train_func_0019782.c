default_hash_funcs(void)
{
	bool has_enabled = false;


	for (int i = 0; i < HASH_FUNCS_N; i++) {
		if (HASH_FUNC_IS_DEFAULT(i) && hash.funcs[i].supported) {
			gtk_toggle_button_set_active(gui.hash_widgets[i].button, true);
			has_enabled = true;
		}
	}

	if (has_enabled)
		return;


	for (int i = 0; i < HASH_FUNCS_N; i++) {
		if (hash.funcs[i].supported) {
			gtk_toggle_button_set_active(gui.hash_widgets[i].button, true);
			return;
		}
	}

	gui_error(_("Failed to enable any supported hash functions."));
	exit(EXIT_FAILURE);
}
