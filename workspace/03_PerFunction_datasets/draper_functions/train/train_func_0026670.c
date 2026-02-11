kpress(But *but, const char *keystr, KeySym sym)  {
  ButOut  retval = BUTOUT_CAUGHT;
  int  newflags = but->flags;
  Ct  *ct = but->iPacket;

  newflags |= BUT_KEYPRESSED|BUT_PRESSED|BUT_LOCKED;
  if (!(but->flags & BUT_KEYPRESSED))  {
    snd_play(&but_downSnd);
    but_newFlags(but, newflags);
    if (ct->pfunc != NULL)
      retval |= ct->pfunc(but);
  }
  return(retval);
}
