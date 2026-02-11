pause_board (gboolean pause)
{

  if(gcomprisBoard==NULL)
    return;

  Paused = pause;

  if(pause){
    if (currentMode == MODE_TUX){
      if (tux_id){
	g_source_remove(tux_id);
	tux_id = 0;
      }
    }
  }
  else {
    if (remainingCards<=0)
      memory_next_level();
    else {
      if (currentMode == MODE_TUX){
	if (to_tux){
	  tux_id = g_timeout_add (2000,
				  (GSourceFunc) tux_play, NULL);
	}
      }
    }

  }
}
