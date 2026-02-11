HandleEnterNotify()
{
  XEnterWindowEvent *ewp = &Event.xcrossing;
  XEvent d;


  if(XCheckTypedWindowEvent (dpy, ewp->window, LeaveNotify, &d))
    {
      StashEventTime(&d);
      if((d.xcrossing.mode==NotifyNormal)&&
	 (d.xcrossing.detail!=NotifyInferior))
	return;
    }


#ifndef NON_VIRTUAL
  if (ewp->window==Scr.PanFrameTop.win
      || ewp->window==Scr.PanFrameLeft.win
      || ewp->window==Scr.PanFrameRight.win
      || ewp->window==Scr.PanFrameBottom.win )
    {
      int delta_x=0, delta_y=0;

      HandlePaging(Scr.EdgeScrollX,Scr.EdgeScrollY,
                   &Event.xcrossing.x_root,&Event.xcrossing.y_root,
                   &delta_x,&delta_y,True);
      return;
    }
#endif

  if(Event.xany.window == Scr.Root)
    {
      if((!(Scr.flags & ClickToFocus))&&(!(Scr.flags & SloppyFocus)))
	{
	  SetFocus(Scr.NoFocusWin,NULL);
	  ClearCirculatedFlag();
	}
      InstallWindowColormaps(NULL);
      return;
    }


  if (!Tmp_win)
    return;

  if(!(Scr.flags & ClickToFocus))
    {
      if(Scr.Focus != Tmp_win)
	{
	  if((Scr.AutoRaiseDelay > 0)&&(!(Tmp_win->flags & VISIBLE)))
	    SetTimer(Scr.AutoRaiseDelay);
	  SetFocus(Tmp_win->w,Tmp_win);
	  ClearCirculatedFlag();
	}
      else
	SetFocus(Tmp_win->w,Tmp_win);
    }
  if((!(Tmp_win->flags & ICONIFIED))&&(Event.xany.window == Tmp_win->w))
    InstallWindowColormaps(Tmp_win);
  else
    InstallWindowColormaps(NULL);
  return;
}
