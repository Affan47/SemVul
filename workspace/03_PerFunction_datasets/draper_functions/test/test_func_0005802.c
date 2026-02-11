RestoreWithdrawnLocation (FvwmWindow *tmp,Bool restart)
{
  int a,b,w2,h2;
  unsigned int bw,mask;
  XWindowChanges xwc;

  if(!tmp)
    return;

  if (XGetGeometry (dpy, tmp->w, &JunkRoot, &xwc.x, &xwc.y,
		    &JunkWidth, &JunkHeight, &bw, &JunkDepth))
    {
      XTranslateCoordinates(dpy,tmp->frame,Scr.Root,xwc.x,xwc.y,
			    &a,&b,&JunkChild);
      xwc.x = a + tmp->xdiff;
      xwc.y = b + tmp->ydiff;
      xwc.border_width = tmp->old_bw;
      mask = (CWX | CWY|CWBorderWidth);


      if(!restart)
	{

	  if((tmp->frame_x < 0)||(tmp->frame_y<0)||
	     (tmp->frame_x >= Scr.MyDisplayWidth)||
	     (tmp->frame_y >= Scr.MyDisplayHeight))
	    {
	      w2 = (tmp->frame_width>>1);
	      h2 = (tmp->frame_height>>1);
	      if (( xwc.x < -w2) || (xwc.x > (Scr.MyDisplayWidth-w2 )))
		{
		  xwc.x = xwc.x % Scr.MyDisplayWidth;
		  if ( xwc.x < -w2 )
		    xwc.x += Scr.MyDisplayWidth;
		}
	      if ((xwc.y < -h2) || (xwc.y > (Scr.MyDisplayHeight-h2 )))
		{
		  xwc.y = xwc.y % Scr.MyDisplayHeight;
		  if ( xwc.y < -h2 )
		    xwc.y += Scr.MyDisplayHeight;
		}
	    }
	}
      XReparentWindow (dpy, tmp->w,Scr.Root,xwc.x,xwc.y);

      if((tmp->flags & ICONIFIED)&&(!(tmp->flags & SUPPRESSICON)))
	{
	  if (tmp->icon_w)
	    XUnmapWindow(dpy, tmp->icon_w);
	  if (tmp->icon_pixmap_w)
	    XUnmapWindow(dpy, tmp->icon_pixmap_w);
	}

      XConfigureWindow (dpy, tmp->w, mask, &xwc);
      XSync(dpy,0);
    }
}
