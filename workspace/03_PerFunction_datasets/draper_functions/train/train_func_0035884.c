game_won()
{
  gamewon = FALSE;
  gcomprisBoard->sublevel++;

  if(gcomprisBoard->sublevel>gcomprisBoard->number_of_sublevel) {

    gcomprisBoard->sublevel=1;
    gcomprisBoard->level++;
    if(gcomprisBoard->level>gcomprisBoard->maxlevel)
      gcomprisBoard->level = gcomprisBoard->maxlevel;

    gc_sound_play_ogg ("sounds/bonus.wav", NULL);
  }
  clockgame_next_level();
}
