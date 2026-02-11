ui_int_set_status (ui_status_t status)
{
  char states[Control_PlayerButtons] = { 0 };
  int live = player_live_stream () || playlist_showing_logo ();
  int i;

  switch (status)
  {
  case UI_STOP:		states[Control_STOP]	= 1; break;
  case UI_PAUSE:	states[Control_PAUSE]	= 1; break;
  case UI_PLAY_SLOW:	states[Control_PLAY]	= 1;
			states[Control_PAUSE]	= 1; break;
  case UI_PLAY:		states[Control_PLAY]	= 1; break;
  case UI_FAST_FORWARD:	states[Control_FASTFWD]	= 1; break;
  default:;
  }

  no_recursion = TRUE;
  for (i = 0; i < Control_PlayerButtons; ++i)
  {
    ui_set_list (c_buttons, i, "active", states[i]);
    if (i == Control_PLAY)
      ui_set_list (c_buttons, i, "sensitive", !!playlist_size ());
    else if (i == Control_PAUSE || i == Control_REWIND || i == Control_FASTFWD)
      ui_set_list (c_buttons, i, "sensitive", !live);
  }
  no_recursion = FALSE;
}
