reviseDims(Can *can)  {
  ButWin  *win = can->win;
  bool change = FALSE;

  if (win->logicalW < win->w)  {
    change = TRUE;
    win->logicalW = win->w;
  }
  if (win->logicalH < win->h)  {
    change = TRUE;
    win->logicalH = win->h;
  }
  if (win->xOff < 0)  {
    change = TRUE;
    win->xOff = 0;
  } else if (win->xOff + win->w > win->logicalW)  {
    change = TRUE;
    win->xOff = win->logicalW - win->w;
  }
  if (win->yOff < 0)  {
    change = TRUE;
    win->yOff = 0;
  } else if (win->yOff + win->h > win->logicalH)  {
    change = TRUE;
    win->yOff = win->logicalH - win->h;
  }
  return(change);
}
