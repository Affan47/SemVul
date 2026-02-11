GetKeyPress(void)
{
	int keycode;

	if (UI_alt_function >= 0)
		return 0x1b;

	PLATFORM_DisplayScreen();

	for (;;) {
		static int rep = KB_DELAY;
		if (PLATFORM_Keyboard() == AKEY_NONE) {
			rep = KB_DELAY;
			break;
		}

		if (rep == 0) {
			rep = KB_AUTOREPEAT;
			break;
		}
		rep--;
		Atari800_Sync();
	}

	do {
#ifdef DIRECTX
		DoEvents();
#endif
		Atari800_Sync();
		keycode = PLATFORM_Keyboard();
		switch (keycode) {
		case AKEY_WARMSTART:
			UI_alt_function = UI_MENU_RESETW;
			return 0x1b;
		case AKEY_COLDSTART:
			UI_alt_function = UI_MENU_RESETC;
			return 0x1b;
		case AKEY_EXIT:
			UI_alt_function = UI_MENU_EXIT;
			return 0x1b;
		case AKEY_UI:
#ifdef DIRECTX
			UI_Run();
#else
			if (UI_alt_function >= 0)
#endif
			return 0x1b;
			break;
		case AKEY_SCREENSHOT:
			UI_alt_function = UI_MENU_PCX;
			return 0x1b;
		case AKEY_SCREENSHOT_INTERLACE:
			UI_alt_function = UI_MENU_PCXI;
			return 0x1b;
		default:
			UI_alt_function = -1;
			break;
		}
	} while (keycode < 0);

	return UI_BASIC_key_to_ascii[keycode];
}
