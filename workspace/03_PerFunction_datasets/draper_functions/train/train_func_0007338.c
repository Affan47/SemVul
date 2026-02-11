displaygameover()
{
  uint8 key;
  bool pressed;

  video_usecolor(6,1);
  video_putstring(30,10,"  GAME OVER  ");
  video_putstring(30,11,winner ? "   YOU WIN   " : "  YOU LOSE   ");
  video_putstring(30,12,"  PRESS ESC  ");
  video_update();
  do{
    key_decode(&key,&pressed);
    key_polling();
  } while (!(pressed&&(key=='@')));
}
