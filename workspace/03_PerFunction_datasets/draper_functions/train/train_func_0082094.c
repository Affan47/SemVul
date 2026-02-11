HandleColormapNotify(void)
{
  XColormapEvent *cevent = (XColormapEvent *)&Event;
  Bool ReInstall = False;


  if(!Tmp_win)
    {
      return;
    }
  if(cevent->new)
    {
      XGetWindowAttributes(dpy,Tmp_win->w,&(Tmp_win->attr));
      if((Tmp_win  == colormap_win)&&(Tmp_win->number_cmap_windows == 0))
	last_cmap = Tmp_win->attr.colormap;
      ReInstall = True;
    }
  else if((cevent->state == ColormapUninstalled)&&
	  (last_cmap == cevent->colormap))
    {

      ReInstall = True;
    }

  while(XCheckTypedEvent(dpy,ColormapNotify,&Event))
    {
      if (XFindContext (dpy, cevent->window,
			FvwmContext, (caddr_t *) &Tmp_win) == XCNOENT)
	Tmp_win = NULL;
      if((Tmp_win)&&(cevent->new))
	{
	  XGetWindowAttributes(dpy,Tmp_win->w,&(Tmp_win->attr));
	  if((Tmp_win  == colormap_win)&&(Tmp_win->number_cmap_windows == 0))
	    last_cmap = Tmp_win->attr.colormap;
	  ReInstall = True;
	}
      else if((Tmp_win)&&
	      (cevent->state == ColormapUninstalled)&&
	      (last_cmap == cevent->colormap))
	{

	  ReInstall = True;
	}
      else if((Tmp_win)&&
	      (cevent->state == ColormapInstalled)&&
	      (last_cmap == cevent->colormap))
	{


	  ReInstall = False;
	}
    }

  if(ReInstall)
    {
      XInstallColormap(dpy,last_cmap);
    }
}
