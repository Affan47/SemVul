print_menu_text(char *InitialText, char *MenuTexts[], int first_menu_item_pos_y, const char *background_name, void *MenuFont)
{
	char open_gl_string[2000];

	InitiateMenu(background_name);


	if (!strcmp(MenuTexts[0], SINGLE_PLAYER_STRING)) {
		SetCurrentFont(FPS_Display_BFont);
		RightPutString(Screen, GameConfig.screen_height - 1 * FontHeight(GetCurrentFont()), VERSION);

		sprintf(open_gl_string, _("OpenGL support compiled: "));
#ifdef HAVE_LIBGL
		strcat(open_gl_string, _(" YES "));
#else
		strcat(open_gl_string, _(" NO "));
#endif
		LeftPutString(Screen, GameConfig.screen_height - 2 * FontHeight(GetCurrentFont()), open_gl_string);
		sprintf(open_gl_string, _("OpenGL output active: "));
		if (use_open_gl)
			strcat(open_gl_string, _(" YES "));
		else
			strcat(open_gl_string, _(" NO "));
		LeftPutString(Screen, GameConfig.screen_height - FontHeight(GetCurrentFont()), open_gl_string);
	}


	if (MenuFont == NULL)
		SetCurrentFont(Menu_BFont);
	else
		SetCurrentFont((BFont_Info *) MenuFont);

}
