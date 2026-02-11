select(int tag)
{
	switch(tag)
	{
	  case MENU_TAG_OK:
		sound.ui_ok();
		manage.abort();
		pop();
		break;
	  case MENU_TAG_CANCEL:
		gsm.change(&st_pause_game);
		break;
	}
}
