showInfo(bool verbose)
{
	if (keymapFailure) {
		printf("[input] can't change kernel keymap table, all shortcuts will NOT work! see SECURITY NOTES section of man page for solution.\n");
	}
}
