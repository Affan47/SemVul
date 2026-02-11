IsClick(int x,int y,unsigned EndMask, XEvent *d)
{
  int xcurrent,ycurrent,total = 0;

  xcurrent = x;
  ycurrent = y;
  while((total < Scr.ClickTime)&&
	(x - xcurrent < 5)&&(x - xcurrent > -5)&&
	(y - ycurrent < 5)&&(y - ycurrent > -5))
    {
      sleep_a_little(10000);
      total+=10;
      if(XCheckMaskEvent (dpy,EndMask, d))
	{
	  StashEventTime(d);
	  return True;
	}
      if(XCheckMaskEvent (dpy,ButtonMotionMask|PointerMotionMask, d))
	{
	  xcurrent = d->xmotion.x_root;
	  ycurrent = d->xmotion.y_root;
	  StashEventTime(d);
	}
    }
  return False;
}
