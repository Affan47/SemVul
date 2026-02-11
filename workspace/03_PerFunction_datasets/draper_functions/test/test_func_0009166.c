grab_key(int key, int keycode, unsigned int mask)
{
	GdkDisplay *display;
	GdkScreen *screen;
	GdkWindow *root;
	gint i;
	display = gdk_display_get_default();


	if (keycodes[key] > 0)
	{
		for (i = 0; i < gdk_display_get_n_screens(display); i++)
		{
			screen = gdk_display_get_screen(display, i);
			if (screen != NULL)
			{
				root = gdk_screen_get_root_window(screen);
				ungrab_mmkey(keycodes[key], masks[key], root);
			}
		}
	}
	keycodes[key] = 0;
	masks[key] = 0;
	keyerror[key] = FALSE;
	if (keycode > 0)
	{
		keycodes[key] = keycode;
		masks[key] = mask;

		for (i = 0; i < gdk_display_get_n_screens(display); i++)
		{
			screen = gdk_display_get_screen(display, i);
			if (screen != NULL)
			{
				root = gdk_screen_get_root_window(screen);
				if (!grab_mmkey(keycodes[key], masks[key], root))
				{

					keyerror[key] = TRUE;
				}
			}
		}
	}
	cfg_set_single_value_as_int(config, "Keybindings", keynames[key], keycodes[key]);
	cfg_set_single_value_as_int(config, "Keymasks", keynames[key], masks[key]);
}
