mmove(But *but, int x, int y)  {
  ButOut  retval = BUTOUT_CAUGHT;
  uint  newflags = but->flags;

  if (mouse_over_but(but, x,y))  {
    if (!(but->flags & BUT_PRESSABLE))
      return(BUTOUT_CAUGHT);
    newflags |= BUT_TWITCHED;
  } else  {
    if (!(but->flags & BUT_PRESSABLE))
      return(0);
    newflags &= ~BUT_TWITCHED;
    if (!(newflags & BUT_LOCKED))
      retval &= ~BUTOUT_CAUGHT;
  }
  if (!(but->flags & BUT_TWITCHED) && (newflags & BUT_TWITCHED))
    butEnv_setCursor(but->win->env, but, butCur_twitch);
  else if ((but->flags & BUT_TWITCHED) && !(newflags & BUT_TWITCHED))
    butEnv_setCursor(but->win->env, but, butCur_idle);
  if (newflags != but->flags)  {
    but_newFlags(but, newflags);
  }
  return(retval);
}
