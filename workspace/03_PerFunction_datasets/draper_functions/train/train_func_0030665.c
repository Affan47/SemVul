M_Menu_Input_f (void)
{
	options_menu (input, "INPUT OPTIONS");

	{
		static menulist_s s_options_invertmouse_box;
		s_options_invertmouse_box.generic.name	= "invert mouse";
		s_options_invertmouse_box.generic.callback = InvertMouseFunc;
		s_options_invertmouse_box.curvalue		= m_pitch->value < 0;
		setup_tickbox (s_options_invertmouse_box);
		Menu_AddItem (&input.panel, &s_options_invertmouse_box);
	}

	add_text (input.window, NULL, 0);

	add_action (input.window, "Key Bindings", CustomizeControlsFunc, 0);

	M_PushMenu_Defaults (input.screen);
}
