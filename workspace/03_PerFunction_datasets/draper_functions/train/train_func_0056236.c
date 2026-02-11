toggle_sound(MENU_ITEM *self)
{
  conf.sound^=1;
  if (conf.sound)
    gbsound_init();
  else
    close_sound();

  return 2;
}
