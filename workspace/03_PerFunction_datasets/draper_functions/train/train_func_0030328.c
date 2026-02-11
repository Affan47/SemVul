grid_mmove(But *but, int x, int y)  {
  uint  newflags = but->flags, retval = BUTOUT_CAUGHT;
  Grid  *grid;

  if (!(but->flags & BUT_PRESSABLE))
    return(BUTOUT_CAUGHT);
  if ((x < but->x) || (y < but->y) ||
      (x >= but->x + but->w) || (y >= but->y + but->h))  {
    newflags &= ~BUT_TWITCHED;
    if (newflags != but->flags)  {
      butEnv_setCursor(but->win->env, but, butCur_idle);
      but_newFlags(but, newflags);
    }
    if (!(newflags & BUT_LOCKED))
      retval = 0;
  } else  {
    newflags |= BUT_TWITCHED;
    if (newflags != but->flags)  {
      grid = but->iPacket;
      assert(MAGIC(grid));
      grid->b->holdStart = butWin_env(but_win(but))->eventTime;
      butEnv_setCursor(but->win->env, but, butCur_twitch);
      but_newFlags(but, newflags);
    }
  }
  return(retval);
}
