press(int button)
{
	switch (button)
	{
	  case BTN_EXIT:
		gsm.change(&st_main_menu);
		break;
	  default:
		sound.ui_play();
		pop();
		break;
	}
}
