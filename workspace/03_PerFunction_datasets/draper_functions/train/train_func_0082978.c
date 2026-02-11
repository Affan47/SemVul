MainMenu_Callback( void *self )
{
	int index;
	menubitmap_s *b;
	b = (menubitmap_s *)self;

	index = b - m_main.bitmaps;
	switch( index ) {
	case 0:
		M_Menu_Game_f();
		break;
	case 1:
		M_Menu_Multiplayer_f();
		break;
	case 2:
		M_Menu_Options_f();
		break;
	case 3:
		M_Menu_Video_f();
		break;
	case 4:
		M_Menu_Quit_f();
		break;
	}
}
