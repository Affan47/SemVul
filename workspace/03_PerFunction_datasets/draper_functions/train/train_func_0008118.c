ui_set_status (ui_status_t newstatus)
{
  pthread_mutex_lock (&status_lock);


  switch (newstatus)
  {
  case UI_CURRENT_STATE:
    ui_int_set_status (status);
    break;
  case UI_STOP:
  case UI_PAUSE:
  case UI_PLAY_SLOW:
  case UI_PLAY:
  case UI_FAST_FORWARD:
    if (playlist_showing_logo ())
      newstatus = UI_STOP;
    ui_int_set_status (status = newstatus);
    break;
  case UI_AUDIO_UNMUTE:	ui_int_set_mute (FALSE); break;
  case UI_AUDIO_MUTE:	ui_int_set_mute (TRUE); break;
  case UI_FS_TOOLBAR:	; break;
  case UI_FS_TOOLBAR_POS:; break;
  case UI_WM_TOOLBAR:	; break;
  case UI_WM_TOOLBAR_SNAP:; break;
  default:;
  }

  pthread_mutex_unlock (&status_lock);
}
