but_delete(But *but)  {
  ButOut  result = 0;
  ButWin  *win = but->win;
  int  x = but->x, y = but->y, w = but->w, h = but->h;

  assert(but != NULL);
  assert(MAGIC(win));
  assert(MAGIC(but));
  if (but->flags)
    but_newFlags(but, 0);
  if (but->destroyCallback)
    but->destroyCallback(but);
  if (but->action->destroy != NULL)
    result = but->action->destroy(but);
  MAGIC_UNSET(but);
  wms_free(but);
  butWin_redraw(win, x,y,w,h);
  return(result);
}
