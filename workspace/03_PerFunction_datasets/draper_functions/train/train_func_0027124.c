boxFilled_resize(But *but, int oldX, int oldY,
			      int oldW, int oldH)  {
  int  x, y, w, h, bw;

  bw = but->win->env->stdButBw;
  x = but->x;
  y = but->y;
  w = but->w;
  h = but->h;

  if ((oldW < 1) || (oldH < 1))  {
    butWin_redraw(but->win, x, y, w, h);
  } else if ((x + w < oldX) || (y + h < oldY) ||
	     (oldX + oldW < x) || (oldY + oldH < y))  {
    butWin_redraw(but->win, oldX, oldY, oldW, oldH);
    butWin_redraw(but->win, x, y, w, h);
  } else  {
    if (x < oldX)
      butWin_redraw(but->win, x, y, oldX + bw - x, h);
    else if (oldX < x)
      butWin_redraw(but->win, oldX, oldY, x + bw - oldX, oldH);

    if (y < oldY)
      butWin_redraw(but->win, x, y, w, oldY + bw - y);
    else if (oldY <  y)
      butWin_redraw(but->win, oldX, oldY, oldW, y + bw - oldY);

    if (x + w < oldX + oldW)
      butWin_redraw(but->win, x + w - bw, oldY,
		    oldX + oldW + bw - x - w, oldH);
    else if (oldX + oldW < x + w)
      butWin_redraw(but->win, oldX + oldW - bw, y,
		    x + w + bw - oldX - oldW, h);

    if (y + h < oldY + oldH)
      butWin_redraw(but->win, oldX, y + h - bw,
		    oldW, oldY + oldH + bw - y - h);
    else if (oldY + oldH < y + h)
      butWin_redraw(but->win, x, oldY + oldH - bw,
		    w, y + h + bw - oldY - oldH);
  }
  return(FALSE);
}
