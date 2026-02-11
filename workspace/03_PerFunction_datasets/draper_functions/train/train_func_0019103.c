SwitchPages(Bool align, Bool ChangeFocus)
{
#ifndef NO_PAGER
  int x,y;
  unsigned int width,height;
  FvwmWindow *tmp_win;
  Window dumwin;

  if(!Scr.FvwmPager)
    return;

  XTranslateCoordinates (dpy, Event.xbutton.window, Scr.Pager_w,
			 Event.xbutton.x, Event.xbutton.y, &x, &y, &dumwin);

  width = Scr.FvwmPager->frame_width - 2*Scr.FvwmPager->boundary_width;
  height = Scr.FvwmPager->frame_height - Scr.FvwmPager->title_height
    - 2*Scr.FvwmPager->boundary_width;

  if(x<0)x=0;
  if(y<0)y=0;
  x = x * (Scr.VxMax+Scr.MyDisplayWidth)/width;
  y = y * (Scr.VyMax+Scr.MyDisplayHeight)/height;
  if(align)
    {
      x = (x/Scr.MyDisplayWidth)*Scr.MyDisplayWidth;
      y = (y/Scr.MyDisplayHeight)*Scr.MyDisplayHeight;
    }
  if(x<0)x=0;
  if(y<0)y=0;
#ifndef NON_VIRTUAL
  MoveViewport(x,y,True);
#endif
  if((ChangeFocus)&&(Scr.flags & ClickToFocus))
    {
      tmp_win = FindCounterpart(Event.xbutton.subwindow);
      if(tmp_win)
	{
	  RaiseWindow(tmp_win);
	  SetFocus(tmp_win->w,tmp_win);
	  ClearCirculatedFlag();
	}
    }
#endif
}
