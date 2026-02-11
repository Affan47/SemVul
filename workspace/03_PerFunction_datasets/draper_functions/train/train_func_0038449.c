press(int button)
{
	if(frame_time < 500)
		return;

	switch (button)
	{
	  case BTN_EXIT:
	  case BTN_NO:
		gsm.change(&st_main_menu);
		break;
	  case BTN_LEFT:
	  case BTN_RIGHT:
	  case BTN_UP:
	  case BTN_DOWN:
	  case BTN_UL:
	  case BTN_UR:
	  case BTN_DL:
	  case BTN_DR:
	  case BTN_FIRE:
	  case BTN_YES:
		sound.ui_play();
		pop();
		break;
	  case BTN_SELECT:
	  case BTN_START:
	  case BTN_PAUSE:
		gsm.change(&st_pause_game);
		break;
	}
}
