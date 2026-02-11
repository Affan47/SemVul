process_error()
{
  gc_sound_play_ogg ("sounds/crash.wav", NULL);
  errors--;
  if(errors==0)
    {
      gamewon = FALSE;
      reversecount_destroy_all_items();
      gc_bonus_display(gamewon, GC_BONUS_SMILEY);
    }
  else
    {
      update_clock(errors);
    }
}
