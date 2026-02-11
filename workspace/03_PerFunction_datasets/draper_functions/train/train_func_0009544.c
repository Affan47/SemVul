fullscreen_saver_deactivate(void)
{
	static gboolean checked = FALSE;
	static gboolean found = FALSE;

	if (!checked)
		{
		checked = TRUE;
		found = file_in_path(XSCREENSAVER_BINARY);
		}

	if (found)
		{
		runcmd(XSCREENSAVER_COMMAND);
		}
}
